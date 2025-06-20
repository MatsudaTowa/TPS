//=============================================
//
//�|�[�Y��UI_�^�C�g����[pause_select_quit.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_quit.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CPauseSelectQuit::TEXTURE_NAME = "data\\TEXTURE\\Quit.png";
//=============================================
//�R���X�g���N�^
//=============================================
CPauseSelectQuit::CPauseSelectQuit(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPauseSelectQuit::~CPauseSelectQuit()
{
}

//=============================================
// ������
//=============================================
HRESULT CPauseSelectQuit::Init()
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
void CPauseSelectQuit::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// �X�V
//=============================================
void CPauseSelectQuit::Update()
{
	CPauseSelect::Update();
}

//=============================================
// �`��
//=============================================
void CPauseSelectQuit::Draw()
{
	CPauseSelect::Draw();
}
