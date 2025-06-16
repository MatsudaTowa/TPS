//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "camera.h"

//=============================================
//�O���錾
//=============================================
class CCamera;

//=============================================
//�J�����X�e�[�g�N���X
//=============================================
class CCameraState
{
public:
	/**
	 * @brief ���R���_
	 * @param [in]�J�����|�C���^
	 */
	virtual void FreeView(CCamera* camera);
	/**
	 * @brief �O�l�̎��_
	 * @param [in]�J�����|�C���^
	 */
	virtual void ThirdView(CCamera* camera);
	/**
	 * @brief �E���g���_
	 * @param [in]�J�����|�C���^
	 */
	virtual void Ult(CCamera* camera);
};

//=============================================
//���R�ȃJ����
//=============================================
class CFreeView : public CCameraState
{
public:
	/**
	 * @brief ���R���_
	 * @param [in]�J�����|�C���^
	 */
	virtual void FreeView(CCamera* camera)override;
private:
	static constexpr float FREEVIEW_LENGTH = 200.0f; //���R���_���̋���
};

//=============================================
//�O�l�̏��
//=============================================
class CThirdView : public CCameraState
{
public:
	/**
	 * @brief �O�l�̎��_
	 * @param [in]�J�����|�C���^
	 */
	virtual void ThirdView(CCamera* camera)override;
private:
	static constexpr float THIRDVIEW_LENGTH = 130.0f; //�T�[�h�p�[�\���r���[���̋���
};

//=============================================
//�E���g���
//=============================================
class CUltCameraState : public CCameraState
{
public:
	/**
	 * @brief �E���g���_
	 * @param [in]�J�����|�C���^
	 */
	virtual void Ult(CCamera* camera) override;
private:
	static constexpr float ULT_LENGTH = 200.0f; //�E���g���̋���
};

#endif // !_PLAYER_STATE_H
