//=============================================
//
//�L�����N�^�[�̃X�e�[�g�p�^�[��[character_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include "character.h"

//=============================================
//�O���錾
//=============================================
class CCharacter;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CCharacterState
{
public:
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character); 
	virtual void Move(CCharacter* character);
};

//=============================================
//�L�����N�^�[�̌����Ă���
//=============================================
class CShotState : public CCharacterState
{
public:
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)override;
};

//=============================================
//�L�����N�^�[�̓����Ă���
//=============================================
class CMoveState : public CCharacterState
{
public:
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
