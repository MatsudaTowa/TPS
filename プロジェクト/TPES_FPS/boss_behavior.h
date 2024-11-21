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
class CBossWandering : public CEnemyMove
{
public:
	CBossWandering();
	~CBossWandering() override;
	void Move(CCharacter* character)override;
private:
	static const int MOVE_FRAME = 60; //�ړ��t���[��
	static const int RIGHT_PARCENT = 50; //�E�̊m��
	static const int LEFT_PARCENT = 100; //���̊m��

	int m_nRight;//���ɍs���m��
	int m_nLeft; //�E�ɍs���m��
	bool m_bRandom; //�ǂ����ɍs�������߂�
	int m_nStateChangeCnt; //�X�e�[�g�ύX�J�E���g
};

//=============================================
//�G�̒Ǐ]�̃X�g���e�W�[
//=============================================
class CBossChase : public CEnemyMove
{
public:
	CBossChase();
	~CBossChase() override;
	void Move(CCharacter* character)override;
private:
	static const int MOVE_FRAME = 60; //�ړ��t���[��
	static const int RIGHT_PARCENT = 50; //�E�̊m��
	static const int LEFT_PARCENT = 100; //���̊m��

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
