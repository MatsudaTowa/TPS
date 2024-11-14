//=============================================
//
//�L�����N�^�[�̃X�e�[�g�p�^�[��[character_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//�L�����N�^�[�̃V���b�g
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
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
	character->m_pAttack->Attack(Allegiance,type,character);
}

//=============================================
//�L�����N�^�[�̓���
//=============================================
void CMoveState::Move(CCharacter* character)
{
	character->m_pMove->Move(character);
}
