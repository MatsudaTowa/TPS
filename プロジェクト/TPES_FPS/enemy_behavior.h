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
class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //�v���C���[�̂ق����������鏈��

private:
	static const int SHOT_FRAME = 180; //�ˌ��t���[��

	int m_nStateChangeCnt;//�X�e�[�g�ύX�J�E���g
};
#endif // !_ENEMY_BEHAVIOR_
