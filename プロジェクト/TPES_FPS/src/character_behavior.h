//=============================================
//
//�L�����N�^�[�̃X�g���e�W�[�p�^�[��[character_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

//=============================================
//�O���錾
//=============================================
class CCharacter;

//=============================================
//�ړ��X�g���e�W�[
//=============================================
class CMove
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CMove();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CMove();
	/**
	 * @brief �ړ�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Move(CCharacter*character) = 0;
protected:
};

//=============================================
//�X�^���̃X�g���e�W�[
//=============================================
class CStan
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CStan();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CStan();
	/**
	 * @brief �X�^��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Stan(CCharacter* character);
private:
};

//=============================================
//�����̃X�g���e�W�[
//=============================================
class CConfusion
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CConfusion();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CConfusion();
	/**
	 * @brief ����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @param [in]��]�J�n�ʒu
	 */
	virtual void Confusion(CCharacter* character, float StartRot_y);
private:
};

//=============================================
//�U���X�g���e�W�[
//=============================================
class CGunAttack
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CGunAttack();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CGunAttack();
	/**
	 * @brief �e�̍U��
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance,CCharacter* character) = 0;
};
#endif
