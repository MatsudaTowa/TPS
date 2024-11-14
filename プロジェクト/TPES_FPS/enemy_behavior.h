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
private:
	static const int MOVE_FRAME = 120; //�ړ��t���[��

	int m_nStateChangeCnt;
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
	void GunAction(CGun* pGun, const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& size, int nDamage, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type);
private:
	static const int SHOT_FRAME = 180; //�ˌ��t���[��

	int m_nStateChangeCnt;
};
#endif // !_ENEMY_BEHAVIOR_
