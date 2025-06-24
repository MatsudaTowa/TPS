//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"
#include "active_scene_state.h"

//=============================================
//�O���錾
//=============================================
class CActiveScene;

/** @brief �ʏ�N���X */
class CGameNormal :public CNormal
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CGameNormal();
	/**
	* @brief �j���[�g��������
	* @param [in]�A�N�e�B�u�V�[���̃|�C���^
	*/
	void Normal(CActiveScene* active_scene) override;
};

/** @brief ��ԏ����N���X */
class CGamePause :public CPause
{
public:
	/**
	* @brief �|�[�Y��ԏ���
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	void Pause(CActiveScene* active_scene) override;
	/**
	 * @brief �|�[�Y�̑I�����ꂽUI�̍X�V���s����
	 * @param [in]�A�N�e�B�u�V�[���̃|�C���^
	 */
	void HandlePoseSelection(CActiveScene* active_scene) override;
	/**
	 * @brief �|�[�Y�L�����Z��
	 * @param [in]�A�N�e�B�u�V�[���̃|�C���^
	 */
	void CancelPause(CActiveScene* active_scene) override;
private:
};

/** @brief �ݒ�N���X */
class CGameSetting :public CSetting
{
public:
	/**
	* @brief �ݒ菈��
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	void Setting(CActiveScene* active_scene) override;
private:
};

#endif // !_GAME_STATE_H_
