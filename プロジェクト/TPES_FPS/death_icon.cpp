//=============================================
//
//���S�A�C�R��[death_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "death_icon.h"
#include "manager.h"

//�e�N�X�`��������
const std::string CDeathIcon::TEXTURE_NAME = "data\\TEXTURE\\death_icon.png";

//=============================================
//�R���X�g���N�^
//=============================================
CDeathIcon::CDeathIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CDeathIcon::~CDeathIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CDeathIcon::Init()
{
	//������
	CObject2D::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CDeathIcon::Uninit()
{
	//�I��
	CObject2D::Uninit();
}


//=============================================
//�X�V
//=============================================
void CDeathIcon::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CDeathIcon::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CDeathIcon* CDeathIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CDeathIcon* pDeathIcon = new CDeathIcon;

	if (pDeathIcon == nullptr) { return nullptr; }

	pDeathIcon->SetPos(pos);
	pDeathIcon->SetSize(size);
	pDeathIcon->SetColor(col);

	pDeathIcon->Init();

	return pDeathIcon;
}
