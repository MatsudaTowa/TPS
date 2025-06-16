//=============================================
//
//�v���C���[�̃X�g���e�W�[�p�^�[��[player_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player.h"

//=============================================
//�v���C���[�̈ړ��̃X�g���e�W�[
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //�W�����v��

	/**
	 * @brief �R���X�g���N�^
	 */
	CPlayerMove();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPlayerMove() override;
	/**
	 * @brief �ړ�
	 * @param [in]�L�����N�^�|�C���^
	 */
	void Move(CCharacter* character)override;
};

//=============================================
//�v���C���[�̍U���̃X�g���e�W�[
//=============================================
class CPlayerAttack : public CGunAttack
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CPlayerAttack();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPlayerAttack() override;
	/**
	 * @brief �e�̍U��
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character) override;
private:
	//�ˌ����̈ړ����Z�̒l
	static constexpr float MOVE_SUBTRACTION = 0.85f;
	/**
	 * @brief �e����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @param [in]�J�����|�C���^
	 * @param [in]�ǂ����̒e��
	 * @param [in]���[�g�J�E���g
	 */
	void ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance,int& nRateCnt);
};

//=============================================
//�v���C���[�̉���̃X�g���e�W�[
//=============================================
class CPlayerAvoidance
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CPlayerAvoidance();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPlayerAvoidance();
	/**
	 * @brief ���
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void Avoidance(CCharacter* character);
private:
	static constexpr float PLAYER_AVOIDANCE_SPEED = 30.0f; //�u�����N�̃X�s�[�h

};
#endif // !_ENEMY_BEHAVIOR_
