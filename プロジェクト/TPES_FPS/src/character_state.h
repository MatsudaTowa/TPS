//=============================================
//
//�L�����N�^�[�̃X�e�[�g�p�^�[��[character_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include "character.h"

//=============================================
//�O���錾
//=============================================
class CCharacter;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CCharacterState
{
public:
	/**
	 * @brief �ŏ��ɌĂ΂��֐�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Start(CCharacter* character);
	/**
	 * @brief �V���b�g
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character); 
	/**
	 * @brief �X�^������
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Stan(CCharacter* character);
	/**
	 * @brief ����
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Confusion(CCharacter* character);
	/**
	 * @brief �ړ�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Move(CCharacter* character);
};

//=============================================
//�L�����N�^�[�̌����Ă���
//=============================================
class CShotState : public CCharacterState
{
public:
	/**
	 * @brief �V���b�g
	 * @param [in]�ǂ����̒e��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)override;
};

//=============================================
//�L�����N�^�[�̃X�^�����
//=============================================
class CStanState : public CCharacterState
{
public:
	/**
	 * @brief �ŏ��ɌĂ΂��֐�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void Start(CCharacter* character) override;
	/**
	 * @brief �X�^��
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Stan(CCharacter* character)override;
private:
	int m_StanCnt; //�X�^���v���J�E���g
};

//=============================================
//�L�����N�^�[�̍������
//=============================================
class CConfusionState : public CCharacterState
{
public:
	/**
	 * @brief �ŏ��ɌĂ΂��֐�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	void Start(CCharacter* character) override;
	/**
	 * @brief ����
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Confusion(CCharacter* character)override;
private:
	float m_StartRot;	//���b�g�̊J�n�l
	bool m_isRight;		//���n��(true:�E false:��)
};

//=============================================
//�L�����N�^�[�̓����Ă���
//=============================================
class CMoveState : public CCharacterState
{
public:
	/**
	 * @brief �ړ�
	 * @param [in]�L�����N�^�[�|�C���^
	 */
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
