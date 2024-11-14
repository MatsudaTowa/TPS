//=============================================
//
//�v���C���[�̃X�g���e�W�[�p�^�[��[player_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player_test.h"

//=============================================
//�v���C���[�̈ړ��̃X�g���e�W�[
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //�W�����v��

	CPlayerMove();
	~CPlayerMove() override;
	void Move(CCharacter* character)override;
};

//=============================================
//�v���C���[�̍U���̃X�g���e�W�[
//=============================================
class CPlayerAttack : public CAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
};
#endif // !_ENEMY_BEHAVIOR_
