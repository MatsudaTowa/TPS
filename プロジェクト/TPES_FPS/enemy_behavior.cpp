//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"
#include "manager.h"
#include "player_test.h"
#include "object.h"

//=============================================
//コンストラクタ
//=============================================
CEnemyMove::CEnemyMove():m_move_vec({0.0f,0.0f,0.0f})
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyMove::~CEnemyMove()
{
}

//=============================================
//移動処理(エネミー)
//=============================================
void CEnemyMove::Move(CCharacter* character)
{
	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(m_move_vec);

	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	CEnemy::Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		Motion = CEnemy::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CEnemy::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(rotMoveY) * character->GetSpeed();
		move.z += cosf(rotMoveY) * character->GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	character->SetRot(rot);
	//移動量代入
	character->SetMove(move);
	//モーション代入
	character->SetMotion(Motion);
}

//=============================================
//コンストラクタ
//=============================================
CEnemyAttack::CEnemyAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyAttack::~CEnemyAttack()
{
}

//=============================================
//攻撃処理(エネミー)
//=============================================
void CEnemyAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	LookAtPlayer(character);
	//TODO:銃のオフセットから
	D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z);
	D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
	0.0f, cosf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed());

	if (character->m_pGun->GetAmmo() > 0)
	{
		character->m_pGun->m_nRateCnt++;
		if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
		{
			character->m_pGun->m_nRateCnt = 0;
			//弾発射
			character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->m_nDamage, Allegiance, type, character->m_pGun);
		}
	}
	else
	{
		character->m_pGun->m_pReload->Reload(character->m_pGun);
	}
}

//=============================================
//プレイヤーのほうを向かせる
//=============================================
void CEnemyAttack::LookAtPlayer(CCharacter* character)
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

				//プレイヤーとの距離算出
				D3DXVECTOR3 Distance = pPlayer_test->GetPos() - character->GetPos();

				//プレイヤーに向ける角度を算出
				float fAngle = atan2f(Distance.x,Distance.z);

				//親クラスからrotを取得
				D3DXVECTOR3 rot = character->GetRot();

				rot.y = fAngle + D3DX_PI;

				character->SetRot(rot);
			}
		}
	}
}
