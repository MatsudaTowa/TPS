//=============================================
//
//カメラのステートパターン[camera_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera_state.h"

//=============================================
//三人称の状態
//=============================================
void CCameraState::ThirdView(CCamera* camera)
{
}

//=============================================
//ウルトの状態
//=============================================
void CCameraState::Ult(CCamera* camera)
{
}

//サードビュー時の距離
const float CThirdView::THIRDVIEW_LENGTH = 130.0f;

//=============================================
//三人称の状態
//=============================================
void CThirdView::ThirdView(CCamera* camera)
{
	camera->SetLength(THIRDVIEW_LENGTH);
}

//ULT時の距離
const float CUltCameraState::ULT_LENGTH = 200.0f;

//=============================================
//ウルトの状態
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
}
