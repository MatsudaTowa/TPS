//=============================================
//
//�u�����N�̕\�L[blink_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "blink_icon.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CBlinkIcon::TEXTURE_NAME = "data\\TEXTURE\\blink.png";

//=============================================
//�R���X�g���N�^
//=============================================
CBlinkIcon::CBlinkIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBlinkIcon::~CBlinkIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CBlinkIcon::Init()
{
	//������
	CObject2D::Init();

	//�e�N�X�`�����擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//�e�N�X�`���o�^
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//���_����
	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlinkIcon::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBlinkIcon::Update()
{
	//�X�V
	CObject2D::Update();

	//���_����
	SetVtx(FLOAT_ONE);
}

//=============================================
//�`��
//=============================================
void CBlinkIcon::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CBlinkIcon* CBlinkIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkIcon* pBlinkIcon = new CBlinkIcon;

	if (pBlinkIcon == nullptr) { return nullptr; }

	pBlinkIcon->SetPos(pos);	//���W�ݒ�
	pBlinkIcon->SetSize(size);	//�T�C�Y�ݒ�
	pBlinkIcon->SetColor(col);	//�F�ݒ�

	//����������
	pBlinkIcon->Init();

	return pBlinkIcon;
}
