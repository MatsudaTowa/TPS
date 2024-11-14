//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CEnemyMove::CEnemyMove():m_nStateChangeCnt(0), m_bRandom(),m_nLeft(),m_nRight()
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
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
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		float move_x = 0.0f;
		if (m_bRandom)
		{
			move_x = 1.0f;
		}
		if (!m_bRandom)
		{
			move_x = -1.0f;
		}
		//移動の方向の単位ベクトル変数
		D3DXVECTOR3 vecDirection(move_x, 0.0f, 0.0f);

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
		++m_nStateChangeCnt;

	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		//次の設定
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_int_distribution<int> number(0, 100);

		//どっちに行くかの確率
		if (number(random) <= m_nRight)
		{
			m_bRandom = true;
			if (m_nRight > 0)
			{//右に進む確率を下げる
				m_nRight -= 5;
			}
		}
		else if (number(random) > m_nRight && number(random) <= m_nLeft)
		{
			m_bRandom = false;
			if (m_nRight < 100)
			{//右に進む確率をあげる
				m_nRight += 5;
			}
		}

		m_nStateChangeCnt = 0;

		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
		//TODO:プレイヤーのほうを向かせる
		D3DXVECTOR3 rot = {0.0f,0.0f,0.0f};
		//rotを代入
		character->SetRot(rot);
		//射撃状態に切り替え
		character->ChangeState(new CShotState);
	}
}

//=============================================
//コンストラクタ
//=============================================
CEnemyAttack::CEnemyAttack() :m_nStateChangeCnt(0)
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
	if (m_nStateChangeCnt < SHOT_FRAME)
	{
		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z);
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * CAssultRifle::DEFAULT_AR_BULLET_SPEED,
		0.0f, cosf(character->GetRot().y + D3DX_PI) * CAssultRifle::DEFAULT_AR_BULLET_SPEED);

		if (character->m_pGun->GetAmmo() > 0)
		{
			character->m_pGun->m_nRateCnt++;
			if (character->m_pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
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
		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= SHOT_FRAME)
	{
		m_nStateChangeCnt = 0;
		//移動状態に切り替え
		character->ChangeState(new CMoveState);
	}
}

//=============================================
//銃の処理(エネミー)
//=============================================
void CEnemyAttack::GunAction(CGun* pGun, const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& size, int nDamage, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type)
{
	
}
