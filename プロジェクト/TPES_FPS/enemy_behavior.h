//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"

//=============================================
//�G�̈ړ��̃X�g���e�W�[
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //�W�����v��

	CEnemyMove();
	~CEnemyMove() override;
	void Move(CCharacter* character)override;
	void SetMoveVec(D3DXVECTOR3 move_vec)
	{
		m_move_vec = move_vec;
	}
private:
	D3DXVECTOR3 m_move_vec;
};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //�v���C���[�̂ق����������鏈��

private:
};
#endif // !_ENEMY_BEHAVIOR_
