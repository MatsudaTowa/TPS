//=============================================
//
//�v���C���[��UI�̘g[player_UI_box.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_UI_box.h"
#include "manager.h"

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
CPlayerUIBox* CPlayerUIBox::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, BOX_TYPE type)
{
	CPlayerUIBox*pUIBox = nullptr;

	switch (type)
	{
	case CPlayerUIBox::BOX_TYPE_LIFE:
		pUIBox = new CLifeUIBox;
		break;
	case CPlayerUIBox::BOX_TYPE_AMMO:
		pUIBox = new CAmmoUIBox;
		break;
	case CPlayerUIBox::BOX_TYPE_SCORE:
		pUIBox = new CScoreUIBox;
		break;
	default:
		break;
	}
	
	if(pUIBox == nullptr) {return nullptr;}

	//���W���
	pUIBox->SetPos(pos);

	//�T�C�Y���
	pUIBox->SetSize(size);

	//�F���
	pUIBox->SetColor(col);

	pUIBox->SetType(OBJECT_TYPE_UI_BOX);

	pUIBox->Init();

	return pUIBox;
}

const std::string CLifeUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_000.png";

//=============================================
//�R���X�g���N�^
//=============================================
CLifeUIBox::CLifeUIBox(int nPriority):CPlayerUIBox(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CLifeUIBox::~CLifeUIBox()
{
}

//=============================================
//������
//=============================================
HRESULT CLifeUIBox::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CLifeUIBox::Uninit()
{
	CPlayerUIBox::Uninit();
}

//=============================================
//�X�V
//=============================================
void CLifeUIBox::Update()
{
	CPlayerUIBox::Update();
}

//=============================================
//�`��
//=============================================
void CLifeUIBox::Draw()
{
	CPlayerUIBox::Draw();
}

const std::string CAmmoUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_001.png";

//=============================================
//�R���X�g���N�^
//=============================================
CAmmoUIBox::CAmmoUIBox(int nPriority) :CPlayerUIBox(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAmmoUIBox::~CAmmoUIBox()
{
}

//=============================================
//������
//=============================================
HRESULT CAmmoUIBox::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAmmoUIBox::Uninit()
{
	CPlayerUIBox::Uninit();
}

//=============================================
//�X�V
//=============================================
void CAmmoUIBox::Update()
{
	CPlayerUIBox::Update();
}

//=============================================
//�`��
//=============================================
void CAmmoUIBox::Draw()
{
	CPlayerUIBox::Draw();
}

const std::string CScoreUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_002.png";

//=============================================
//�R���X�g���N�^
//=============================================
CScoreUIBox::CScoreUIBox(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CScoreUIBox::~CScoreUIBox()
{
}

//=============================================
//������
//=============================================
HRESULT CScoreUIBox::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CScoreUIBox::Uninit()
{
	CPlayerUIBox::Uninit();
}

//=============================================
//�X�V
//=============================================
void CScoreUIBox::Update()
{
	CPlayerUIBox::Update();
}

//=============================================
//�`��
//=============================================
void CScoreUIBox::Draw()
{
	CPlayerUIBox::Draw();
}
