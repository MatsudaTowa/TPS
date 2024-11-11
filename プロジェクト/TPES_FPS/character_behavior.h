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
	virtual void Move(D3DXVECTOR3 vecDirection, float fRotMoveY,CCharacter*character, int motion) = 0;
protected:
};

class CDush : public CMove
{
public:
	CDush();
	~CDush() override;
	void Move(D3DXVECTOR3 vecDirection, float fRotMoveY, CCharacter* character,int motion)override;
};

//=============================================
//�U���X�g���e�W�[
//=============================================
class CAttack
{
public:
	CAttack();
	virtual ~CAttack();
	virtual void Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, 
	CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character) = 0;
};

class CPlayerAttack : public CAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
		CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun*pGun, CCharacter* character) override;
};

class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
		CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character) override;
};
#endif
