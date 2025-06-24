//=============================================
//
//�|�[�Y���Ƃ���UI[close_pause_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "close_pause_UI.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CClosePauseUI::TEXTURE_NAME = "data\\TEXTURE\\cloase_pause_UI.png";

//=============================================
// �R���X�g���N�^
//=============================================
CClosePauseUI::CClosePauseUI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CClosePauseUI::~CClosePauseUI()
{
}

//=============================================
// ������
//=============================================
HRESULT CClosePauseUI::Init()
{
	//�e�N�X�`�����擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	SetColor(COLOR_WHITE);
	//�e�N�X�`���o�^
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CObject2D::Init();
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CClosePauseUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CClosePauseUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// �`��
//=============================================
void CClosePauseUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CClosePauseUI* CClosePauseUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CClosePauseUI* pPauseUI = new CClosePauseUI;
	if (pPauseUI == nullptr)
	{
		return nullptr;
	}
	pPauseUI->SetPos(pos);
	pPauseUI->SetSize(size);
	pPauseUI->Init();
	return pPauseUI;

}
