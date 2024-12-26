//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.h]
//Auther Matsuda Towa
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
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CCameraState
{
public:
	virtual void FreeView(CCamera* camera);
	virtual void ThirdView(CCamera* camera);
	virtual void Ult(CCamera* camera);
};

//=============================================
//���R�ȃJ����
//=============================================
class CFreeView : public CCameraState
{
public:
	virtual void FreeView(CCamera* camera)override;
private:
	static const float FREEVIEW_LENGTH; //�T�[�h�p�[�\���r���[���̋���
};

//=============================================
//�L�����N�^�[�̒ʏ���
//=============================================
class CThirdView : public CCameraState
{
public:
	virtual void ThirdView(CCamera* camera)override;
private:
	static const float THIRDVIEW_LENGTH; //�T�[�h�p�[�\���r���[���̋���
};

//=============================================
//�L�����N�^�[�̃E���g���
//=============================================
class CUltCameraState : public CCameraState
{
public:
	virtual void Ult(CCamera* camera) override;
private:
	static const float ULT_LENGTH; //�E���g���̋���
};

#endif // !_PLAYER_STATE_H
