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
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);
	void Stay(CCharacter* character);
	void NextMove_X(CCharacter* character);
	static const int TRANSITION_FRAME = 60;
	static const int MOVE_FRAME = 60; //�ړ��t���[��
	static const int STAY_FRAME = 60; //���ʂ����Ď~�܂鎞��
	static const int RIGHT_PARCENT = 50; //0�ȏ�50�����Ȃ�E��
	static const int LEFT_PARCENT = 100; //50�ȏ�100�����Ȃ獶��

	int m_TransitionCnt;
	int m_nRight;//���ɍs���m��
	int m_nLeft; //�E�ɍs���m��
	int m_nStateChangeCnt; //�X�e�[�g�ύX�J�E���g
	int m_nStayCnt; //�X�e�C��ԃJ�E���g
	bool m_bRandom; //�ǂ����ɍs�������߂�
	bool m_bDamage;
};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CNormalAttack : public CEnemyGunAttack
{
public:
	CNormalAttack();
	~CNormalAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	static const int LOST_FRAME = 180;
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);
	int m_nLostCnt;
};

#endif // !_ENEMY_BEHAVIOR_
