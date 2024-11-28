//=============================================
//
//ボスのストラテジーパターン[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"
#include "wave_boss.h"
#include "player_test.h"
#include "boss_enemy.h"
#include "block.h"
#include "object.h"

//=============================================
//コンストラクタ
//=============================================
CBossWandering::CBossWandering():m_MoveIdx(0), m_StopCnt(0), m_isMove()
{
	m_isMove = true;
}

//=============================================
//デストラクタ
//=============================================
CBossWandering::~CBossWandering()
{
}

//=============================================
//徘徊
//=============================================
void CBossWandering::Wandering(CBossEnemy* boss)
{
	if (m_isMove)
	{
		//移動先の情報取得(引数が移動先のポイントの配列番号)
		CMovePoint* pMovePoint = CWave_Boss::GetMovePoint(m_MoveIdx);

		//対象の位置への方向情報
		D3DXVECTOR3 point = { pMovePoint->GetPos().x - boss->GetPos().x,0.0f,pMovePoint->GetPos().z - boss->GetPos().z };

		// 目的地との距離を計算
		float distance = sqrtf(point.x * point.x + point.z * point.z);

		// 到達判定用の閾値
		const float threshold = 0.5f; // 距離が定数以下なら到達とする（必要に応じて調整）

		// まだ目的地に到達していない場合のみ移動処理を行う
		if (distance > threshold)
		{
			//対象物との角度計算
			float angle = atan2f(point.x, point.z);

			D3DXVECTOR3 move = boss->GetMove();

			move.x += sinf(angle) * boss->GetSpeed();
			move.z += cosf(angle) * boss->GetSpeed();
			//親クラスからrotを取得
			D3DXVECTOR3 rot = boss->GetRot();
			rot.y = angle + D3DX_PI;
			//rotを代入
			boss->SetRot(rot);
			//移動量代入
			boss->SetMove(move);
		}
		else
		{//到達していたら
			m_isMove = false;

			D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
			boss->SetMove(move);

			//次の移動先の抽選
			PickNextMovePoint(pMovePoint);
		}
	}
	else if (!m_isMove)
	{//動かない状態なら
		//指定フレーム分止まる
		StopCnt();
	}
}

//=============================================
//指定フレーム分止まる
//=============================================
void CBossWandering::StopCnt()
{
	++m_StopCnt;
	if (m_StopCnt > STOP_FRAME)
	{
		m_StopCnt = 0;
		m_isMove = true;
	}
}

//=============================================
//次の移動先の抽選
//=============================================
void CBossWandering::PickNextMovePoint(CMovePoint* pMovePoint)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, pMovePoint->GetNumPoint());
	//ランダムで位置指定
  	m_MoveIdx = number(random);
	if (m_MoveIdx >= pMovePoint->GetNumPoint())
	{
		m_MoveIdx = 0;
	}
}

//=============================================
//徘徊のデバッグ表示
//=============================================
void CBossWandering::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n[ボス進む位置]%d"
		,m_MoveIdx );
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CBossChase::CBossChase():m_bTargetPlayer(false)
{
}

//=============================================
//デストラクタ
//=============================================
CBossChase::~CBossChase()
{
}

//=============================================
//追跡
//=============================================
void CBossChase::Chase(CBossEnemy* boss, CObject* obj)
{
	CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(obj);

	//プレイヤーの位置への方向情報
	D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

	// 目的地との距離を計算
	float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

	D3DXVec3Normalize(&Vector, &Vector);

	// 到達判定用の閾値
	const float threshold = 200.0f; // 距離が定数以下なら到達とする 遠距離武器だから近づきすぎないように調整

	// レイキャストを実行し、障害物があるか判定
	m_bTargetPlayer = PerformRaycast(boss->GetPos(), Vector, boss->LOST_PLAYER_DISTANCE);

	if (m_bTargetPlayer)
	{
		//プレイヤーに向かって動かす
		MovetoPlayer(distance, threshold, Vector, boss);
	}
	else
	{
		boss->ChangeState(new CWanderingState);
	}
}

//=============================================
//プレイヤーに向かって動かす
//=============================================
void CBossChase::MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss)
{
	// まだ目的地に到達していない場合のみ移動処理を行う
	if (distance > threshold)
	{
		//対象物との角度計算
		float angle = atan2f(Vector.x, Vector.z);

		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(angle) * boss->GetSpeed();
		move.z += cosf(angle) * boss->GetSpeed();
		//親クラスからrotを取得
		D3DXVECTOR3 rot = boss->GetRot();
		rot.y = angle + D3DX_PI;
		//rotを代入
		boss->SetRot(rot);
		//移動量代入
		boss->SetMove(move);
	}
	else
	{
		D3DXVECTOR3 move = {0.0f,0.0f,0.0f};
		//移動量代入
		boss->SetMove(move);
	}
}

//=============================================
//障害物があるか判定
//=============================================
bool CBossChase::PerformRaycast(const D3DXVECTOR3& startPos, const D3DXVECTOR3& direction, float maxDistance)
{
	// レイの終点を計算
	D3DXVECTOR3 endPos = startPos + direction * maxDistance;

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++) 
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
				// バウンディングボックス取得
				D3DXVECTOR3 boxMin = pBlock->GetMinPos();
				D3DXVECTOR3 boxMax = pBlock->GetMaxPos();
				// ブロックとの衝突判定
				if (CManager::GetInstance()->GetColision()->CheckIntersectRay(startPos, direction, boxMin, boxMax))
				{
					// 障害物が間にある場合
					return false;
				}
			}
		}
	}
	// 障害物がなく、プレイヤーまでレイが到達する場合
	return true;
}

//=============================================
//追跡のデバッグ表示
//=============================================
void CBossChase::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	if (m_bTargetPlayer)
	{
		sprintf(&aStr[0], "\n\n\n\n対象:プレイヤー");
	}
	else if (!m_bTargetPlayer)
	{
		sprintf(&aStr[0], "\n\n\n\n対象:ブロック");
	}
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CBossGunAttack::CBossGunAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CBossGunAttack::~CBossGunAttack()
{
}

//=============================================
//攻撃
//=============================================
void CBossGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CBossEnemy::Motion_Type Motion;
	Motion = CBossEnemy::Motion_Type::MOTION_ATTACK;
	//モーション代入
	character->SetMotion(Motion);
	if (character->m_pGunAttack != nullptr)
	{
		character->m_pGun->m_nRateCnt++;
		if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
		{
			character->m_pGun->m_nRateCnt = 0;
			//銃から発射
			D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41,
				character->m_apModel[14]->GetMtxWorld()._42, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI));

			D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
				0.0f, cosf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed());
			//弾発射
			character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->m_nDamage, Allegiance, type, character->m_pGun);
		}
	}
}