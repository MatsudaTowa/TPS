//=============================================
//
//�X���[�N�̕\�L[smoke_icon.h]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_icon.h"
#include "manager.h"

//�e�N�X�`��������
const std::string CSmokeIcon::TEXTURE_NAME = "data\\TEXTURE\\smoke_UI.png";

//=============================================
//�R���X�g���N�^
//=============================================
CSmokeIcon::CSmokeIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmokeIcon::~CSmokeIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CSmokeIcon::Init()
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
void CSmokeIcon::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmokeIcon::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CSmokeIcon::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CSmokeIcon* CSmokeIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CSmokeIcon* pSmokeIcon = new CSmokeIcon;

	if (pSmokeIcon == nullptr) { return nullptr; }

	pSmokeIcon->SetPos(pos);
	pSmokeIcon->SetSize(size);
	pSmokeIcon->SetColor(col);

	pSmokeIcon->Init();

	return pSmokeIcon;
}
