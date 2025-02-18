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

//=============================================
//�E���g�̏��
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
	camera->ThirdViewCamera();
}
