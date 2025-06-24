//=============================================
//
//�|�[�Y��UI_���g���C[pause_select_setting.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_setting.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CPauseSelectSetting::TEXTURE_NAME = "data\\TEXTURE\\Setting.png";
//=============================================
// �R���X�g���N�^
//=============================================
CPauseSelectSetting::CPauseSelectSetting(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPauseSelectSetting::~CPauseSelectSetting()
{
}

//=============================================
// ������
//=============================================
HRESULT CPauseSelectSetting::Init()
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
void CPauseSelectSetting::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// �X�V
//=============================================
void CPauseSelectSetting::Update()
{
	CPauseSelect::Update();
}

//=============================================
// �`��
//=============================================
void CPauseSelectSetting::Draw()
{
	CPauseSelect::Draw();
}
