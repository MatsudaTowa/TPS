//=============================================
//
//�L�����N�^�[�̃X�g���e�W�[�p�^�[��[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

//=============================================
//�O���錾
//=============================================
class CCharacter;

//=============================================
//�ړ��X�g���e�W�[
//=============================================
class CMove
{
public:
	CMove();
	virtual ~CMove();
	virtual void Move(CCharacter*character) = 0;
protected:
};

//=============================================
//�����̃X�g���e�W�[
//=============================================
class CStan
{
public:
	CStan();
	virtual ~CStan();
	virtual void Stan(CCharacter* character);
private:
};

//=============================================
//�����̃X�g���e�W�[
//=============================================
class CConfusion
{
public:
	CConfusion();
	virtual ~CConfusion();
	virtual void Confusion(CCharacter* character, float StartRot_y);
private:
};

//=============================================
//�U���X�g���e�W�[
//=============================================
class CGunAttack
{
public:
	CGunAttack();
	virtual ~CGunAttack();
	virtual void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CCharacter* character) = 0;
};
#endif
