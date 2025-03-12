//=============================================
//
//�u�����N�̐����̔w�i[blink_back_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "blink_back_UI.h"
#include "manager.h"

//�e�N�X�`���p�X
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
	//�e�N���X�̏�����
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
void CBlinkBackUI::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBlinkBackUI::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();

	//���_����
	SetVtx(FLOAT_ONE);
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

	pBlinkBackUI->SetPos(pos);		//�ʒu�ݒ�
	pBlinkBackUI->SetSize(size);	//�T�C�Y�ݒ�
	pBlinkBackUI->SetColor(col);	//�J���[�ݒ�

	//������
	pBlinkBackUI->Init();

	return pBlinkBackUI;
}
