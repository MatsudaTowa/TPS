//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[boss_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "enemy.h"

//=============================================
//�G�̜p�j�̃X�g���e�W�[
//=============================================
class CBossWandering
{
public:
	CBossWandering();
	~CBossWandering();
	void Wandering(CEnemy* enemy);
private:
};

//=============================================
//�G�̒Ǐ]�̃X�g���e�W�[
//=============================================
class CBossChase
{
public:
	CBossChase();
	~CBossChase();
	void Chase(CEnemy* enemy);
private:

};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CBossAttack : public CEnemyAttack
{
public:
	CBossAttack();
	~CBossAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	static const int SHOT_STATE_FRAME = 180; //�ˌ��t���[��

	int m_nStateChangeCnt;//�X�e�[�g�ύX�J�E���g
};
#endif // !_ENEMY_BEHAVIOR_
