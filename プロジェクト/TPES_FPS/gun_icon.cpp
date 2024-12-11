//=============================================
//
//�e�̕\��[gun_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun_icon.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CGunIcon::CGunIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGunIcon::~CGunIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CGunIcon::Init()
{
	//������
	CObject2D::Init();

	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGunIcon::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGunIcon::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CGunIcon::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//�`��
//=============================================
CGunIcon* CGunIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ICON_TYPE type)
{
	CGunIcon* pGunIcon = nullptr;

	switch (type)
	{
	case CGunIcon::ICON_TYPE_AR:
		pGunIcon = new CARIcon;
		break;
	default:
		break;
	}

	if(pGunIcon == nullptr) {return nullptr;}

	pGunIcon->SetPos(pos);
	pGunIcon->SetSize(size);
	pGunIcon->SetColor(col);

	pGunIcon->Init();

	return pGunIcon;
}

//�e�N�X�`��������
const std::string CARIcon::TEXTURE_NAME = "data\\TEXTURE\\ak.png";
//=============================================
//�R���X�g���N�^
//=============================================
CARIcon::CARIcon(int nPriority):CGunIcon(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CARIcon::~CARIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CARIcon::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//������
	CGunIcon::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CARIcon::Uninit()
{
	//�I��
	CGunIcon::Uninit();
}

//=============================================
//�X�V
//=============================================
void CARIcon::Update()
{
	//�X�V
	CGunIcon::Update();
}

//=============================================
//�`��
//=============================================
void CARIcon::Draw()
{
	//�`��
	CGunIcon::Draw();
}
