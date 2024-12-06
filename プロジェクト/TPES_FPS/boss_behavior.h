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
	void Chase(CBossEnemy* boss, CObject* obj);
	void MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss);
	void DrawDebug();
private:
	BOOL m_bTargetPlayer;
};

class CBossStan
{
public:
	CBossStan();
	~CBossStan();
	void Stan(CBossEnemy* boss);
};

//=============================================
//�����̃X�g���e�W�[
//=============================================
class CBossConfusion
{
public:
	CBossConfusion();
	~CBossConfusion();
	void Confusion(CBossEnemy* boss, float StartRot_y);
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CBossEnemy* boss);
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector,CBossEnemy* boss);
private:
	static constexpr float LOOK_RANGE = 1.57f; //���n���͈�
	static constexpr int NUM_TURN = 2; //���n����
	int m_TurnCnt; //���񌩓n������
	bool m_isRight; //���n��(true:�E false:��)
};

//=============================================
//�G�̏e�̍U���̃X�g���e�W�[
//=============================================
class CBossGunAttack : public CEnemyGunAttack
{
public:
	CBossGunAttack();
	~CBossGunAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;

private:
	static const int SHOT_STATE_FRAME = 180; //�ˌ��t���[��

	int m_nStateChangeCnt;//�X�e�[�g�ύX�J�E���g
};

//=============================================
//�ːi�U���̃X�g���e�W�[
//=============================================
class CBossTackle
{
public:
	static const int TACKLE_DAMAGE = 30;

	CBossTackle();
	~CBossTackle();
	void Tackle(CBossEnemy* boss);
private:
	static const int STAY_FLAME = 120; //�ːi�܂ł̑ҋ@����
	static const int TACKLE_FLAME = 150; //�^�b�N������
	void LookAtPlayer(CCharacter* character); //�v���C���[�̂ق����������鏈��
	int m_StayCnt;
	int m_TackleCnt;
	bool m_isTackle;
};
#endif // !_ENEMY_BEHAVIOR_
