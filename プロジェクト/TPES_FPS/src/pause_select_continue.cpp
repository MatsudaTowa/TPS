//=============================================
//
//�|�[�Y��UI_�R���e�B�j���[[pause_select_continue.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_continue.h"

//=============================================
//�R���X�g���N�^
//=============================================
CPauseSelectContinue::CPauseSelectContinue(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPauseSelectContinue::~CPauseSelectContinue()
{
}

//=============================================
// ������
//=============================================
HRESULT CPauseSelectContinue::Init()
{
	CPauseSelect::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CPauseSelectContinue::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// �X�V
//=============================================
void CPauseSelectContinue::Update()
{
	CPauseSelect::Update();
}

//=============================================
// �`��
//=============================================
void CPauseSelectContinue::Draw()
{
	CPauseSelect::Draw();
}

