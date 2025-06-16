//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"
#include "enemy_reaction_UI.h"

//=============================================
//�G�̈ړ��̃X�g���e�W�[
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //�W�����v��

	/**
	 * @brief �R���X�g���N�^
	 */
	CEnemyMove();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemyMove() override;
	/**
	 * @brief �ړ�����
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void Move(CCharacter* character)override;
	/**
	 * @brief �ړ������ݒ�
	 * @param [in]�ړ�����
	 */
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
	/**
	 * @brief �R���X�g���N�^
	 */
	CEnemyStan();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemyStan() override;
	/**
	 * @brief �X�^��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void Stan(CCharacter* character)override;
private:
};

//=============================================
//�G�̍����̃X�g���e�W�[
//=============================================
class CEnemyConfusion : public CConfusion
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CEnemyConfusion();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemyConfusion() override;
	/**
	 * @brief ����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @param [in]��]�J�n�ʒu
	 */
	void Confusion(CCharacter* character, float StartRot_y)override;
	/**
	 * @brief ��]����
	 * @param [in]����
	 * @param [in]�ŏI���B�_
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character);
private:
	static constexpr float CORRECTION_VALUE = 40.0f; //���A�N�V������UI�𐶐�����ۂ�Y�̕␳�l
	static const D3DXVECTOR3 SIZE; //���A�N�V������UI�̃T�C�Y
	static constexpr float ROT_MOVE = 0.02f; //���n���ړ��l
	static constexpr float CORRECTION_VALUE_Y = 20.0f; //���C���΂�Y�̕␳�l

	static constexpr float LOOK_RANGE = 1.57f; //���n���͈�
	static constexpr int NUM_TURN = 2; //���n����

	CEnemy_Reaction_UI* m_pReaction;
	int m_TurnCnt; //���񌩓n������
	bool m_isRight; //���n��(true:�E false:��)
};

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CEnemyGunAttack : public CGunAttack
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CEnemyGunAttack();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemyGunAttack() override;
	/**
	 * @brief �e�̍U��
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�|�C���^
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance,CCharacter* character) override;
	/**
	 * @brief �v���C���[�̂ق�����������
	 * @param [in]�L�����N�^�|�C���^
	 */
	void LookAtPlayer(CCharacter* character);

private:
};
#endif // !_ENEMY_BEHAVIOR_
