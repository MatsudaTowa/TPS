#include "normal_enemy_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CNormalMove::CNormalMove():m_nStateChangeCnt(0), m_bRandom(), m_nLeft(), m_nRight()
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
}

//=============================================
//デストラクタ
//=============================================
CNormalMove::~CNormalMove()
{
}

//=============================================
//移動
//=============================================
void CNormalMove::Move(CCharacter* character)
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

		//横にしか移動しないのでxに値代入
		SetMoveVec({ move_x,0.0f,0.0f });

		//親クラスの移動を呼ぶ
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		NextMove_X(character);
	}
}

//=============================================
//動く処理が終わったら次の方向を抽選
//=============================================
void CNormalMove::NextMove_X(CCharacter* character)
{
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
	//射撃状態に切り替え
	character->ChangeState(new CShotState);
}

//=============================================
//コンストラクタ
//=============================================
CNormalAttack::CNormalAttack():m_nStateChangeCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CNormalAttack::~CNormalAttack()
{
}

//=============================================
//攻撃
//=============================================
void CNormalAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	if (m_nStateChangeCnt < SHOT_STATE_FRAME)
	{
		CEnemyAttack::Attack(Allegiance,type,character);
		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= SHOT_STATE_FRAME)
	{
		m_nStateChangeCnt = 0;
		//移動状態に切り替え
		character->ChangeState(new CMoveState);
	}
}
