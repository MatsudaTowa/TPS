//=============================================
//
//�����[�h�̕\�L[reload_icon.cpp]
//Author Matsuda Towa
//
//=============================================
#include "reload_txt.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CReloatTxt::TEXTURE_NAME = "data\\TEXTURE\\reloading.png";

//=============================================
// �R���X�g���N�^
//=============================================
CReloatTxt::CReloatTxt(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CReloatTxt::~CReloatTxt()
{
}

//=============================================
// ������
//=============================================
HRESULT CReloatTxt::Init()
{
	//������
	CObject2D::Init();

	//�e�N�X�`���o�^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
// �I��
//=============================================
void CReloatTxt::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CReloatTxt::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(FLOAT_ONE);
}

//=============================================
// �`��
//=============================================
void CReloatTxt::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CReloatTxt* CReloatTxt::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CReloatTxt* pTxt = new CReloatTxt;

	if (pTxt == nullptr) { return nullptr; }

	pTxt->SetPos(pos);		//�ʒu�ݒ�
	pTxt->SetSize(size);	//�T�C�Y�ݒ�
	pTxt->SetColor(col);	//�J���[�ݒ�

	pTxt->Init();			//�������ݒ�

	return pTxt;
}
