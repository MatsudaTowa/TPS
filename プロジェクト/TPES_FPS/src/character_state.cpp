//=============================================
//
//�L�����N�^�[�̃X�e�[�g�p�^�[��[character_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CCharacterState::Start(CCharacter* character)
{
}

//=============================================
//�L�����N�^�[�̃V���b�g
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
}

//=============================================
//�L�����N�^�[�̃X�^��
//=============================================
void CCharacterState::Stan(CCharacter* character)
{
}


//=============================================
//�L�����N�^�[�̍���
//=============================================
void CCharacterState::Confusion(CCharacter* character)
{
}

//=============================================
//�L�����N�^�[�̓���
//=============================================
void CCharacterState::Move(CCharacter* character)
{
}

//=============================================
//�L�����N�^�[�̃V���b�g
//=============================================
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	character->GetGunAttack()->GunAttack(Allegiance,character);
}

//=============================================
//�L�����N�^�[�̓���
//=============================================
void CMoveState::Move(CCharacter* character)
{
	CMove* move = character->GetMoveStrategy();
	if (move != nullptr)
	{
		move->Move(character);
	}
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CStanState::Start(CCharacter* character)
{
	//�J�E���g���Z�b�g
	m_StanCnt = 0;
}

//=============================================
//�L�����N�^�[�̃X�^�����
//=============================================
void CStanState::Stan(CCharacter* character)
{
	const int StanFrame = character->GetStanFrame();

	if (m_StanCnt < StanFrame)
	{
		++m_StanCnt;

		CStan* stan = character->GetStan();

		if (stan != nullptr)
		{
			stan->Stan(character);
		}
	}
	if (m_StanCnt >= StanFrame)
	{
		m_StanCnt = 0;

		//�ˌ���ԂɑJ��
		character->ChangeState(new CShotState);
		return;
	}
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CConfusionState::Start(CCharacter* character)
{
	m_StartRot = character->GetRot().y;
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
//�L�����N�^�[�̍������
//=============================================
void CConfusionState::Confusion(CCharacter* character)
{
	CConfusion* confusion = character->GetConfusion();
	if (confusion != nullptr)
	{
		confusion->Confusion(character, m_StartRot);
	}
}
