//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera_state.h"

//=============================================
//�O�l�̂̏��
//=============================================
void CCameraState::ThirdView(CCamera* camera)
{
}

//=============================================
//�E���g�̏��
//=============================================
void CCameraState::Ult(CCamera* camera)
{
}

//�T�[�h�r���[���̋���
const float CThirdView::THIRDVIEW_LENGTH = 130.0f;

//=============================================
//�O�l�̂̏��
//=============================================
void CThirdView::ThirdView(CCamera* camera)
{
	camera->SetLength(THIRDVIEW_LENGTH);
}

//ULT���̋���
const float CUltCameraState::ULT_LENGTH = 200.0f;

//=============================================
//�E���g�̏��
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
}
