//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[boss_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "boss_enemy.h"
#include "move_point.h"

//=============================================
//�O���錾
//=============================================
class CBossEnemy;

//=============================================
//�G�̜p�j�̃X�g���e�W�[
//=============================================
class CBossWandering
{
public:
	//�~�܂��Ă�t���[����
	static const int STOP_FRAME = 30;
	CBossWandering();
	~CBossWandering();
	void Wandering(CBossEnemy* boss);
	void StopCnt();
	void PickNextMovePoint(CMovePoint* pMovePoint);
	void DrawDebug();
private:
	int m_MoveIdx; //�ړ���̔ԍ�
	int m_StopCnt; //�~�܂��Ă�J�E���g
	bool m_isMove; //�������ǂ���
};

//=============================================
//�G�̒Ǐ]�̃X�g���e�W�[
//=============================================
class CBossChase
{
public:
	CBossChase();
	~CBossChase();
	void Chase(CBossEnemy* boss);
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
