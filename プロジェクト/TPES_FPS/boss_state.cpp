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
