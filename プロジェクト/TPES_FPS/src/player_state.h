//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "ult.h"

//=============================================
//�O���錾
//=============================================
class CActivePlayer;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CPlayerState
{
public:
	/**
	 * @brief �ʏ�
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Default(CActivePlayer* player);
	/**
	 * @brief �E���g
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Ult(CActivePlayer* player);
	/**
	 * @brief ���
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Avoidance(CActivePlayer* player);
	/**
	 * @brief ������΂���
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Blown(CActivePlayer* player);
};

//=============================================
//�L�����N�^�[�̒ʏ���
//=============================================
class CDefaultState : public CPlayerState
{
public:
	/**
	 * @brief �ʏ�
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Default(CActivePlayer* player)override;
};

//=============================================
//�L�����N�^�[�̃E���g���
//=============================================
class CUltState : public CPlayerState
{
public:
	/**
	 * @brief �E���g
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Ult(CActivePlayer* player) override;
};

//=============================================
//�L�����N�^�[�̉�����
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	/**
	 * @brief ���
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Avoidance(CActivePlayer* player) override;
};

//=============================================
//�L�����N�^�[�̐�����΂�����
//=============================================
class CBlownState : public CPlayerState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CBlownState();
	/**
	 * @brief ������΂���
	 * @param [in]�����v���C���[�|�C���^
	 */
	virtual void Blown(CActivePlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
