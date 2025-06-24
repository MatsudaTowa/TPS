//=============================================
//
//���x�̕���UI[sens_txt_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "sens_txt_UI.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CSensTxtUI::TEXTURE_NAME = "data\\TEXTURE\\sens_UI.png";
//=============================================
// �R���X�g���N�^
//=============================================
CSensTxtUI::CSensTxtUI(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CSensTxtUI::~CSensTxtUI()
{
}

//=============================================
// ������
//=============================================
HRESULT CSensTxtUI::Init()
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
void CSensTxtUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CSensTxtUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// �`��
//=============================================
void CSensTxtUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CSensTxtUI* CSensTxtUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CSensTxtUI* pTxt = new CSensTxtUI;
	if (pTxt == nullptr)
	{
		return nullptr;
	}
	pTxt->SetPos(pos);
	pTxt->SetSize(size);
	pTxt->Init();
	return pTxt;

}

