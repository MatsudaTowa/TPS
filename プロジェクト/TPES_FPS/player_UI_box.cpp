//=============================================
//
//�v���C���[��UI�̘g[player_UI_box.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_UI_box.h"
#include "manager.h"

const std::string CPlayerUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box.png";

//=============================================
//�R���X�g���N�^
//=============================================
CPlayerUIBox::CPlayerUIBox(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerUIBox::~CPlayerUIBox()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayerUIBox::Init()
{
	//�e�N���X�̏�����
	CObject2D::Init();

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPlayerUIBox::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayerUIBox::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();

	SetVtx(1.0f);

}

//=============================================
//�`��
//=============================================
void CPlayerUIBox::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CPlayerUIBox* CPlayerUIBox::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CPlayerUIBox*pUIBox = new CPlayerUIBox;
	
	if(pUIBox == nullptr) {return nullptr;}

	//���W���
	pUIBox->SetPos(pos);

	//�T�C�Y���
	pUIBox->SetSize(size);

	//�F���
	pUIBox->SetColor(col);

	pUIBox->SetType(OBJECT_TYPE_UI_BOX);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//pUIBox->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pUIBox->Init();

	return pUIBox;
}
