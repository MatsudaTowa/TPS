//=============================================
//
//�|�[�Y��UI_���g���C[pause_select_retry.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_retry.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CPauseSelectRetry::TEXTURE_NAME = "data\\TEXTURE\\Retry.png";
//=============================================
//�R���X�g���N�^
//=============================================
CPauseSelectRetry::CPauseSelectRetry(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPauseSelectRetry::~CPauseSelectRetry()
{
}

//=============================================
// ������
//=============================================
HRESULT CPauseSelectRetry::Init()
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
void CPauseSelectRetry::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// �X�V
//=============================================
void CPauseSelectRetry::Update()
{
	CPauseSelect::Update();
}

//=============================================
// �`��
//=============================================
void CPauseSelectRetry::Draw()
{
	CPauseSelect::Draw();
}
