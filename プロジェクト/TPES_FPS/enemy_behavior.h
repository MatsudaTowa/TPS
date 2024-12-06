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
//�G�̃X�^���̃X�g���e�W�[
//=============================================
class CEnemyStan : public CStan
{
public:
	CEnemyStan();
	~CEnemyStan() override;
	void Stan(CCharacter* character)override;
private:
};

//=============================================
//�G�̍����̃X�g���e�W�[
//=============================================
class CEnemyConfusion : public CConfusion
{
public:
	CEnemyConfusion();
	~CEnemyConfusion() override;
	void Confusion(CCharacter* character, float StartRot_y)override;
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character);
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);
private:
	static constexpr float LOOK_RANGE = 1.57f; //���n���͈�
	static constexpr int NUM_TURN = 2; //���n����
	int m_TurnCnt; //���񌩓n������
	bool m_isRight; //���n��(true:�E false:��)
};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CEnemyGunAttack : public CGunAttack
{
public:
	CEnemyGunAttack();
	~CEnemyGunAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //�v���C���[�̂ق����������鏈��

private:
};
#endif // !_ENEMY_BEHAVIOR_
