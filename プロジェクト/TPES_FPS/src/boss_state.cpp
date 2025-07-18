//=============================================
//
//ボスのステートパターン[boss_state.h]
//Author Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CChaseState::CChaseState() : 
m_PlayTackleCnt(INT_ZERO)		//タックルに移り変わるまでのカウント
{
}

//=============================================
//デストラクタ
//=============================================
CChaseState::~CChaseState()
{
	//タックルに移り変わるまでのカウント初期化
	m_PlayTackleCnt = INT_ZERO;
}

//=============================================
//ボスの追跡状態
//=============================================
void CChaseState::Chase(CBossEnemy* boss)
{
	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		//プレイヤーを探す
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}

		if (boss->GetBossChase() != nullptr)
		{
			boss->GetBossChase()->Chase(boss, pObj);
		}
	}

	++m_PlayTackleCnt;

	if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
	{//タックル実行フレームに到達したら
		//ステート切り替え
		m_PlayTackleCnt = INT_ZERO;

		boss->ChangeState(new CTackleState);
	}

	boss->GetGunAttack()->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, boss);
}

//=============================================
//ボスの追跡状態デバッグ
//=============================================
void CChaseState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n追跡");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CBossStanState::Start([[maybe_unused]] CBossEnemy* boss)
{
	//スタンカウント初期化
	m_StanCnt = INT_ZERO;
}

//=============================================
//最後に呼ばれる関数
//=============================================
void CBossStanState::End([[maybe_unused]] CBossEnemy* boss)
{
}

//=============================================
//ボスのスタン状態
//=============================================
void CBossStanState::Stan(CBossEnemy* boss)
{
	//スタンカウント加算
	++m_StanCnt;

	CStan* stan = boss->GetStan();

	if (stan != nullptr)
	{
		stan->Stan(boss);
	}

	if (m_StanCnt >= STAN_FRAME)
	{
		m_StanCnt = INT_ZERO;

		//射撃状態に遷移
		boss->ChangeState(new CWanderingState);
	}
}

//=============================================
//ボスのスタン状態デバッグ
//=============================================
void CBossStanState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\nスタン");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CWanderingState::CWanderingState() :
m_TransitionCnt(INT_ZERO),			//ステート移り変わり猶予カウント
m_bDamage(false),					//ダメージを食らっているか
m_TargetRot(VEC3_RESET_ZERO)		//目的の方向
{
}

//=============================================
//デストラクタ
//=============================================
CWanderingState::~CWanderingState()
{
}

//=============================================
//ボスの徘徊状態
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
	if (boss->GetLife() < CBossEnemy::LOW_HP)
	{//体力が少なかったら
		//暴走状態に
		boss->ChangeState(new CRampageState);
	}
	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		m_bDamage = true;

		for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
			if (pObj == nullptr)
			{//ヌルポインタなら
				continue;
			}

			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//プレイヤーを探す
			if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{//プレイヤーじゃなかったら
				continue;
			}

			CPlayer* player = dynamic_cast<CPlayer*>(pObj);

			//プレイヤーとの距離算出
			D3DXVECTOR3 Distance = player->GetPos() - boss->GetPos();

			//プレイヤーに向ける角度を算出
			float fAngle = atan2f(Distance.x, Distance.z);

			//親クラスからrotを取得
			D3DXVECTOR3 rot = boss->GetRot();

			rot.y = fAngle + D3DX_PI;

			m_TargetRot = rot;
		}
	}

	if (m_bDamage)
	{
		++m_TransitionCnt;

		//親クラスからrotを取得
		D3DXVECTOR3 rot = boss->GetRot();

		boss->SetRot(rot);

		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_TransitionCnt = INT_ZERO;
			boss->ChangeState(new CChaseState);
		}
	}
	else if(!m_bDamage)
	{
		if (boss->GetBossWandering() != nullptr)
		{
			boss->GetBossWandering()->Wandering(boss);
			//プレイヤーの位置への方向情報
			D3DXVECTOR3 Vector = boss->GetPos() + boss->GetMove() - boss->GetPos();

			if (!boss->PerformRaycast_Player(Vector, boss).hit)
			{//プレイヤーにレイが当たっていなかったら
				//この関数を抜ける
				return;
			}

			if (boss->PerformRaycast_Block(Vector, boss).hit)
			{//ブロックに当たっていたら
				if (boss->PerformRaycast_Block(Vector, boss).distance > boss->PerformRaycast_Player(Vector, boss).distance)
				{//ブロックより手前にいるときに
					boss->ChangeState(new CChaseState);
				}
			}
			else if (!boss->PerformRaycast_Block(Vector, boss).hit)
			{
				boss->ChangeState(new CChaseState);
			}
		}
	}
}

//=============================================
//ボスの徘徊状態デバッグ
//=============================================
void CWanderingState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n徘徊");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CTackleState::CTackleState()
{
}

//=============================================
//デストラクタ
//=============================================
CTackleState::~CTackleState()
{
	
}

//=============================================
//最初の一回だけ呼ばれる関数
//=============================================
void CTackleState::Start([[maybe_unused]] CBossEnemy* boss)
{
}

//=============================================
//最後の一回だけ呼ばれる関数
//=============================================
void CTackleState::End(CBossEnemy* boss)
{
	if (boss->GetDashEffect() != nullptr)
	{
		boss->GetDashEffect()->Uninit();
		boss->SetDashEffect(nullptr);
	}
	if (boss->GetTackleCharge() != nullptr)
	{
		boss->GetTackleCharge()->Uninit();
		boss->SetTackleCharge(nullptr);
	}
}

//=============================================
//ボスのタックル処理
//=============================================
void CTackleState::Tackle(CBossEnemy* boss)
{
	if (boss->GetBossTackle() != nullptr)
	{
		boss->GetBossTackle()->Tackle(boss);
	}
}

//=============================================
//ボスのタックル状態デバッグ
//=============================================
void CTackleState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n突進");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//UIのサイズ
const D3DXVECTOR3 CConfusionBossState::SIZE = { 40.0f,40.0f,0.0f };

//=============================================
//コンストラクタ
//=============================================
CConfusionBossState::CConfusionBossState()
{
	m_pReaction = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CConfusionBossState::~CConfusionBossState()
{
	if (m_pReaction != nullptr)
	{
		m_pReaction->Uninit();
		m_pReaction = nullptr;
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CConfusionBossState::Start(CBossEnemy* boss)
{
	if (m_pReaction == nullptr)
	{
		m_pReaction = CEnemy_Reaction_UI::Create({ boss->m_apModel[1]->GetMtxWorld()._41,
			boss->m_apModel[1]->GetMtxWorld()._42 + CORRECTION_VALUE,
			boss->m_apModel[1]->GetMtxWorld()._43 }, SIZE, CEnemy_Reaction_UI::REACTION::REACTION_CONFUSION);
	}

	m_StartRot = boss->GetRot().y;

	if (m_StartRot < HALF_PI && m_StartRot > -HALF_PI)
	{
		m_isRight = false;
	}
	else if (m_StartRot > HALF_PI && m_StartRot < -HALF_PI)
	{
		m_isRight = true;
	}
}

//=============================================
//ボスの混乱処理
//=============================================
void CConfusionBossState::Confusion(CBossEnemy* boss)
{
	if (boss->GetBossConfusion() != nullptr)
	{
		//自分の方向を取得
		D3DXVECTOR3 vec = { sinf(boss->GetRot().y + D3DX_PI), FLOAT_ZERO, cosf(boss->GetRot().y + D3DX_PI) };

		// レイキャストを実行し、障害物があるか判定
		if (boss->PerformRaycast_Player(vec, boss).hit)
		{
			if (boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				if (boss->PerformRaycast_Smoke(vec, boss).distance > boss->PerformRaycast_Player(vec, boss).distance)
				{//ブロックより手前にいるときに
					boss->ChangeState(new CChaseState);
				}
			}
			else if (!boss->PerformRaycast_Block(vec, boss).hit && !boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				boss->ChangeState(new CChaseState);
			}
		}

		boss->GetBossConfusion()->Confusion(boss, m_StartRot);
	}

	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		boss->ChangeState(new CBossStanState);
	}
}

//=============================================
//ボスの混乱状態デバッグ
//=============================================
void CConfusionBossState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n混乱");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初の一回だけ呼ばれる関数
//=============================================
void CSearchState::Start([[maybe_unused]] CBossEnemy* boss)
{
	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタじゃなければ
		 //タイプ取得
			continue;
		}

		CObject::OBJECT_TYPE type = pObj->GetType();

		//敵との当たり判定
		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
			m_TargetPos = pPlayer->GetPos();
		}
	}
}

//=============================================
//プレイヤー探索
//=============================================
void CSearchState::Search(CBossEnemy* boss)
{
	if (boss->GetBossSearch() != nullptr)
	{
		boss->GetBossSearch()->Search(boss, m_TargetPos);
	}
}

//=============================================
//ボスの探索状態デバッグ
//=============================================
void CSearchState::DrawDebug()
{
}

//=============================================
//最初の一回だけ呼ばれる関数
//=============================================
void CRampageState::Start(CBossEnemy* boss)
{
	boss->SetMove(VEC3_RESET_ZERO);
}

//=============================================
//最後の一回だけ呼ばれる関数
//=============================================
void CRampageState::End(CBossEnemy* boss)
{
	if (boss->GetDashEffect() != nullptr)
	{
		boss->GetDashEffect()->Uninit();
		boss->SetDashEffect(nullptr);
	}
}

//=============================================
//ボスの暴走状態
//=============================================
void CRampageState::Rampage(CBossEnemy* boss)
{
	if (boss->GetBossRampage() != nullptr)
	{
		boss->GetBossRampage()->Rampage(boss);
	}
}

//=============================================
//ボスの暴走状態デバッグ
//=============================================
void CRampageState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n暴走");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
