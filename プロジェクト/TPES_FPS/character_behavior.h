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
//�U���X�g���e�W�[
//=============================================
class CAttack
{
public:
	CAttack();
	virtual ~CAttack();
	virtual void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CCharacter* character) = 0;
};
#endif
