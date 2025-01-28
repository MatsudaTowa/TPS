//=============================================
//
//�u�����N�̐����̔w�i[blink_back_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "blink_back_UI.h"
#include "manager.h"

//�e�N�X�`��������
const std::string CBlinkBackUI::TEXTURE_NAME = "data\\TEXTURE\\blink_back.png";

//=============================================
//�R���X�g���N�^
//=============================================
CBlinkBackUI::CBlinkBackUI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBlinkBackUI::~CBlinkBackUI()
{
}

//=============================================
//������
//=============================================
HRESULT CBlinkBackUI::Init()
{
	CObject2D::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlinkBackUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBlinkBackUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CBlinkBackUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CBlinkBackUI* CBlinkBackUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkBackUI* pBlinkBackUI = new CBlinkBackUI;

	if (pBlinkBackUI == nullptr) { return nullptr; }

	pBlinkBackUI->SetPos(pos);
	pBlinkBackUI->SetSize(size);
	pBlinkBackUI->SetColor(col);

	pBlinkBackUI->Init();

	return pBlinkBackUI;
}
