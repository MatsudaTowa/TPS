//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[boss_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "boss_enemy.h"
#include "move_point.h"
#include "enemy_reaction_UI.h"

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
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossWandering();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossWandering();
	/**
	 * @brief �p�j����
	 * @param [in]�{�X�̃|�C���^
	 */
	void Wandering(CBossEnemy* boss);

	/**
	 * @brief �f�o�b�O�\��
	 */
	void DrawDebug(); 
private:
	static const int STOP_FRAME = 30;	//�~�܂��Ă�t���[����

	static constexpr float THRESHOLD = 0.5f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j
	/**
	 * @brief �~�܂��Ă鎞�Ԍv��
	 */
	void StopCnt();
	/**
	 * @brief ���̈ړ��|�C���g���I
	 * @param [in]�ړ��|�C���g
	 */
	void PickNextMovePoint(CMovePoint* pMovePoint);

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
	/**
	 * @brief�R���X�g���N�^
	 */
	CBossChase();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossChase();
	/**
	 * @brief �ǂ���������
	 * @param [in]�{�X�̃|�C���^
	 * @param [in]�ǂ������Ώۂ̃I�u�W�F�N�g
	 */
	void Chase(CBossEnemy* boss, CObject* obj);
	/**
	 * @brief �f�o�b�O�\��
	 */
	void DrawDebug();
private:
	static constexpr float THRESHOLD = 200.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j
	/**
	 * @brief �v���C���[�Ɍ������ē���
	 * @param [in]����
	 * @param [in]���B臒l
	 * @param [in]Vector
	 * @param boss
	 */
	void MovetoPlayer(float distance, const float threshold, D3DXVECTOR3 Vector, CBossEnemy* boss);

	BOOL m_bTargetPlayer;		//���C���������Ă���true�ɂ��v���C���[��ǂ�������
};

//=============================================
//�G�̃X�^���̃X�g���e�W�[
//=============================================
class CBossStan
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossStan();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossStan();
	/**
	 * @brief �X�^������
	 * @param [in]�{�X�̃|�C���^
	 */
	void Stan(CBossEnemy* boss);
};

//=============================================
//�����̃X�g���e�W�[
//=============================================
class CBossConfusion
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossConfusion();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossConfusion();
	/**
	 * @brief ��������
	 * @param [in]�{�X�̃|�C���^
	 * @param [in]�����̊J�n�ʒu
	 */
	void Confusion(CBossEnemy* boss, float StartRot_y);

	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector,CBossEnemy* boss);
private:
	static constexpr float LOOK_RANGE = 1.6f; //���n���͈�
	static constexpr float ROT_MOVE = 0.01f; //���n���ړ��l
	static constexpr float CORRECTION_VALUE_Y = 20.0f; //���C���΂�Y�̕␳�l
	static constexpr int NUM_TURN = 2; //���n����
	/**
	 * @brief �����̈ړ�
	 * @param [in][out]����
	 * @param [in]���B�ʒu
	 * @param [in]�{�X�̃|�C���g
	 */
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CBossEnemy* boss);
	int m_TurnCnt; //���񌩓n������
	bool m_isRight; //���n��(true:�E false:��)
};

//=============================================
//�G�̏e�̍U���̃X�g���e�W�[
//=============================================
class CBossGunAttack : public CEnemyGunAttack
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossGunAttack();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossGunAttack() override;

	/**
	 * @brief �e�̍U��
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�[�̃|�C���^
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character) override;

private:
	static const int SHOT_STATE_FRAME = 90; //�ˌ��t���[��

	int m_nStateChangeCnt;//�X�e�[�g�ύX�J�E���g
};

//=============================================
//�ːi�U���̃X�g���e�W�[
//=============================================
class CBossTackle
{
public:
	static const int TACKLE_DAMAGE = 30;
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossTackle();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossTackle();
	/**
	 * @brief �^�b�N��
	 * @param [in]�{�X�̃|�C���^
	 */
	void Tackle(CBossEnemy* boss);

private:
	static const int STAY_FLAME = 180; //�ːi�܂ł̑ҋ@����
	static const int CORRECTION_FLAME = 15; //�G�t�F�N�g�ƍ��킹��Ƃ����̂Ńt���[����␳
	static const int TACKLE_FLAME = 60; //�^�b�N������
	static constexpr float CORRECTION_VALUE_Y = 50.0f; //�^�b�N���G�t�F�N�g�𐶐�����ۂ�Y�̕␳�l

	/**
	 * @brief �v���C���[�̂ق�����������
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void LookAtPlayer(CCharacter* character);
	int m_StayCnt;				//�Ƃǂ܂�J�E���g
	int m_TackleCnt;			//�^�b�N���p���J�E���g
	bool m_isTackle;			//�^�b�N�����邩�ǂ���
	float m_effect_reduction;	//�G�t�F�N�g�̃T�C�Y�k��
};

//=============================================
//�T���̃X�g���e�W�[
//=============================================
class CBossSearch
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossSearch();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossSearch();
	/**
	 * @brief �T��
	 * @param [in]�{�X�|�C���^
	 * @param [in]�ڕW�̈ʒu
	 */
	void Search(CBossEnemy* boss,D3DXVECTOR3 TargetPos);
private:
	static constexpr float THRESHOLD = 0.5f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j

};

//=============================================
//�\���̃X�g���e�W�[
//=============================================
class CBossRampage
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossRampage();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossRampage();
	/**
	 * @brief �\��
	 * @param [in]�{�X�|�C���^
	 */
	void Rampage(CBossEnemy* boss);
private:
	static const int NUM_TARGETPOINT = 4; //�O���̃|�C���g��
	static const int NUM_RAPS = 3; //�������邩
	static constexpr float THRESHOLD = 5.5f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j
	static const int OUTER_CIRCUMFERENCE[NUM_TARGETPOINT]; //�O���̔ԍ�
	int m_MoveIdx; //�ړ���̔ԍ�
	int m_LapCnt; //�����������̃J�E���g
};
#endif // !_ENEMY_BEHAVIOR_
