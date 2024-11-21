#include "normal_enemy_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CNormalMove::CNormalMove():m_nStateChangeCnt(0), m_bRandom(), m_nLeft(), m_nRight()
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalMove::~CNormalMove()
{
}

//=============================================
//�ړ�
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

		//���ɂ����ړ����Ȃ��̂�x�ɒl���
		SetMoveVec({ move_x,0.0f,0.0f });

		//�e�N���X�̈ړ����Ă�
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		NextMove_X(character);
	}
}

//=============================================
//�����������I������玟�̕����𒊑I
//=============================================
void CNormalMove::NextMove_X(CCharacter* character)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, 100);

	//�ǂ����ɍs�����̊m��
	if (number(random) <= m_nRight)
	{
		m_bRandom = true;
		if (m_nRight > 0)
		{//�E�ɐi�ފm����������
			m_nRight -= 5;
		}
	}
	else if (number(random) > m_nRight && number(random) <= m_nLeft)
	{
		m_bRandom = false;
		if (m_nRight < 100)
		{//�E�ɐi�ފm����������
			m_nRight += 5;
		}
	}

	m_nStateChangeCnt = 0;

	character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
	//�ˌ���Ԃɐ؂�ւ�
	character->ChangeState(new CShotState);
}

//=============================================
//�R���X�g���N�^
//=============================================
CNormalAttack::CNormalAttack():m_nStateChangeCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalAttack::~CNormalAttack()
{
}

//=============================================
//�U��
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
		//�ړ���Ԃɐ؂�ւ�
		character->ChangeState(new CMoveState);
	}
}
