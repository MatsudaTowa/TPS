//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera_state.h"
#include "manager.h"

//=============================================
//���R���_
//=============================================
void CCameraState::FreeView(CCamera* camera)
{
}

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

const float CFreeView::FREEVIEW_LENGTH = 200.0f;

//=============================================
//���R������
//=============================================
void CFreeView::FreeView(CCamera* camera)
{
	camera->SetLength(FREEVIEW_LENGTH);

	//����
	camera->InputMove();
	
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_V))
	{
		camera->ChangeCameraState(new CThirdView);
	}
}

//�T�[�h�r���[���̋���
const float CThirdView::THIRDVIEW_LENGTH = 130.0f;

//=============================================
//�O�l�̂̏��
//=============================================
void CThirdView::ThirdView(CCamera* camera)
{
	camera->SetLength(THIRDVIEW_LENGTH);

	camera->ThirdViewCamera();


	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_B))
	{
		camera->ChangeCameraState(new CFreeView);
	}
#endif // _DEBUG

}

//ULT���̋���
const float CUltCameraState::ULT_LENGTH = 200.0f;

//=============================================
//�E���g�̏��
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
	camera->ThirdViewCamera();
}
