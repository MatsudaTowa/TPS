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
	virtual void Start(CCharacter* character);
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character); 
	virtual void Stan(CCharacter* character);
	virtual void Confusion(CCharacter* character);
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
//�L�����N�^�[�̃X�^�����
//=============================================
class CStanState : public CCharacterState
{
public:
	void Start(CCharacter* character) override;
	virtual void Stan(CCharacter* character)override;
private:
	static constexpr int STAN_FRAME = 600; //�X�^������
	int m_StanCnt; //�X�^���v���J�E���g
};

//=============================================
//�L�����N�^�[�̍������
//=============================================
class CConfusionState : public CCharacterState
{
public:
	void Start(CCharacter* character) override;
	virtual void Confusion(CCharacter* character)override;
private:
	float m_StartRot;
	bool m_isRight; //���n��(true:�E false:��)
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
