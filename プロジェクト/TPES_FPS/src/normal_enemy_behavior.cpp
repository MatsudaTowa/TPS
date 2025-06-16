//=============================================
//
//�m�[�}���G�l�~�[�̃X�g���e�W�[�p�^�[��[normal_enemy_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "normal_enemy_behavior.h"
#include "smoke_range.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CNormalMove::CNormalMove():
m_TransitionCnt(INT_ZERO),		
m_nStateChangeCnt(INT_ZERO),
m_nStayCnt(INT_ZERO), 
m_bRandom(), 
m_nLeft(),
m_nRight(),
m_bDamage(false)
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
	if (m_bDamage)
	{
		++m_TransitionCnt;
		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_bDamage = false;
			m_TransitionCnt = INT_ZERO;

			//�ˌ���Ԃ�
			character->ChangeState(new CShotState);
			return;
		}
	}
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		float move_x = FLOAT_ZERO;

		if (m_bRandom)
		{
			move_x = FLOAT_ONE;
		}
		if (!m_bRandom)
		{
			move_x = -FLOAT_ONE;
		}

		//���ɂ����ړ����Ȃ��̂�x�ɒl���
		SetMoveVec({ move_x,0.0f,0.0f });

		//�e�N���X�̈ړ����Ă�
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		Stay(character);
	}

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	CCharacter::RayHitInfo HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if ((HitPlayerInfo.hit
	&&!HitBlockInfo.hit))
	{//�_���[�W��Ԃ������̓��C���v���C���[�ɓ������Ă�����
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);

		//�ˌ���Ԃ�
		character->ChangeState(new CShotState);
	}

	if (character->GetState() == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		m_bDamage = true;
	}
}

//=============================================
//���ʂ����Ď~�܂�
//=============================================
void CNormalMove::Stay(CCharacter* character)
{
	character->SetRot(VEC3_RESET_ZERO);

	if (m_nStayCnt < STAY_FRAME)
	{
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
		++m_nStayCnt;
	}
	if (m_nStayCnt >= STAY_FRAME)
	{
		m_nStateChangeCnt = INT_ZERO;
		m_nStayCnt = INT_ZERO;
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
}

//=============================================
//�R���X�g���N�^
//=============================================
CNormalAttack::CNormalAttack():m_nLostCnt(0)
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
void CNormalAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	LookAtPlayer(character);

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	//D3DXVec3Normalize(&vec, &vec);

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	CCharacter::RayHitInfo HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);

	if (HitPlayerInfo.hit)
	{
		if (character->PerformRaycast_Block(vec, character).hit)
		{//�u���b�N�ɓ������Ă�����
			if (character->PerformRaycast_Block(vec, character).distance > HitPlayerInfo.distance)
			{//�u���b�N����O�ɂ���Ƃ���
				CEnemyGunAttack::GunAttack(Allegiance, character);
			}
			else if (character->PerformRaycast_Block(vec, character).distance < HitPlayerInfo.distance)
			{
				++m_nLostCnt;
			}
		}
		else if (!character->PerformRaycast_Block(vec, character).hit)
		{
			m_nLostCnt = 0;
			CEnemyGunAttack::GunAttack(Allegiance, character);
		}
	}

	if (character->PerformRaycast_Smoke(vec, character).hit || m_nLostCnt > LOST_FRAME)
	{//�X���[�N�ɓ������Ă���
		character->ChangeState(new CConfusionState);
		return;;
	}
}