//=============================================
//
//�|�[�Y��UI_�R���e�B�j���[[pause_select_continue.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_continue.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CPauseSelectContinue::TEXTURE_NAME = "data\\TEXTURE\\Continue.png";

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
	//�e�N�X�`�����擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���o�^
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
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

