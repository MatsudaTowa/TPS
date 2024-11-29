//=============================================
//
//ボスのステートパターン[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player_test.h"

//=============================================
//ボスの追跡状態(基底では何もしない)
//=============================================
void CBossState::Chase(CBossEnemy* boss)
{
}

//=============================================
//ボスの徘徊状態(基底では何もしない)
//=============================================
void CBossState::Wandering(CBossEnemy* boss)
{
}

//=============================================
//ボスのタックル状態(基底では何もしない)
//=============================================
void CBossState::Tackle(CBossEnemy* boss)
{
}

//=============================================
//ボスのデバッグ情報
//=============================================
void CBossState::DrawDebug()
{
}

//=============================================
//コンストラクタ
//=============================================
CChaseState::CChaseState() : m_PlayTackleCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CChaseState::~CChaseState()
{
}

//=============================================
//ボスの追跡状態
//=============================================
void CChaseState::Chase(CBossEnemy* boss)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				if (boss->m_pChase != nullptr)
				{
					boss->m_pChase->Chase(boss, pObj);
				}
			}
		}
	}

	//TODO:ステートパターンで
	if (boss->GetLife() < HP_LOW)
	{//HPが低い状態だったら

		boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);

		++m_PlayTackleCnt;

		if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
		{//タックル実行フレームに到達したら
			m_PlayTackleCnt = 0;
			//ステート切り替え
			boss->ChangeState(new CTackleState);
		}
	}
	else if (boss->GetLife() >= HP_LOW)
	{
		boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);
	}

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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//ボスの徘徊状態
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				//プレイヤーの位置への方向情報
				D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

				// 目的地との距離を計算
				float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

				if (distance < boss->FIND_PLAYER_DISTANCE)
				{//近かったら
					boss->ChangeState(new CChaseState); //追跡状態に変更
				}
				else if (boss->m_pWandering != nullptr)
				{
					boss->m_pWandering->Wandering(boss);
				}
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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//ボスのタックル処理
//=============================================
void CTackleState::Tackle(CBossEnemy* boss)
{
	if (boss->m_pTackle != nullptr)
	{
		boss->m_pTackle->Tackle(boss);
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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
