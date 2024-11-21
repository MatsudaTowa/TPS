//=============================================
//
//�m�[�}���G�l�~�[�̃X�g���e�W�[�p�^�[��[normal_enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_BEHAVIOR_
#define _NORMAL_ENEMY_BEHAVIOR_
#include "enemy_behavior.h"
#include "enemy.h"

//=============================================
//�G�̈ړ��̃X�g���e�W�[
//=============================================
class CNormalMove : public CEnemyMove
{
public:
	static const int MAX_JUMPCNT = 2; //�W�����v��

	CNormalMove();
	~CNormalMove() override;
	void Move(CCharacter* character)override;
private:
	void NextMove_X(CCharacter* character);
	static const int MOVE_FRAME = 60; //�ړ��t���[��
	static const int RIGHT_PARCENT = 50; //�E�̊m��
	static const int LEFT_PARCENT = 100; //���̊m��

	int m_nRight;//���ɍs���m��
	int m_nLeft; //�E�ɍs���m��
	bool m_bRandom; //�ǂ����ɍs�������߂�
	int m_nStateChangeCnt; //�X�e�[�g�ύX�J�E���g
};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CNormalAttack : public CEnemyAttack
{
public:
	CNormalAttack();
	~CNormalAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	static const int SHOT_STATE_FRAME = 180; //�ˌ��t���[��

	int m_nStateChangeCnt;//�X�e�[�g�ύX�J�E���g
};

#endif // !_ENEMY_BEHAVIOR_
