//=============================================
//
//�L�����N�^�[�̃X�e�[�g�p�^�[��[character_state.cpp]
//Auther Matsuda Towa
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
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
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
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	character->m_pGunAttack->GunAttack(Allegiance,type,character);
}

//=============================================
//�L�����N�^�[�̓���
//=============================================
void CMoveState::Move(CCharacter* character)
{
	if (character->m_pMove != nullptr)
	{
		character->m_pMove->Move(character);
	}
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CConfusionState::Start(CCharacter* character)
{
	m_StartRot = character->GetRot().y;
	if (m_StartRot < D3DX_PI * 0.5f && m_StartRot > -D3DX_PI * 0.5f)
	{
		m_isRight = false;
	}
	else if (m_StartRot > D3DX_PI * 0.5f && m_StartRot < -D3DX_PI * 0.5f)
	{
		m_isRight = true;
	}
}

//=============================================
//�L�����N�^�[�̍������
//=============================================
void CConfusionState::Confusion(CCharacter* character)
{
	if (character->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		character->ChangeState(new CShotState);
	}
	if (character->m_pConfusion != nullptr)
	{
		character->m_pConfusion->Confusion(character, m_StartRot);
	}
}
