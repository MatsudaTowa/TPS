//=============================================
//
//�A�N�V����UI�̕\�L[action_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "action_UI.h"
#include "manager.h"

//=============================================
//�e�N�X�`���p�X
//=============================================
const std::string CAction_UI::TEXTURE_NAME[CAction_UI::ACTION_MAX]
{
	"data\\TEXTURE\\move_txt.png",
	"data\\TEXTURE\\shotmode_txt.png",
	"data\\TEXTURE\\shot_txt.png",
	"data\\TEXTURE\\reload_txt.png",
	"data\\TEXTURE\\ult_txt.png",
	"data\\TEXTURE\\smoke_txt.png",
};

//=============================================
//�R���X�g���N�^
//=============================================
CAction_UI::CAction_UI(int nPriority) :CObject2D(nPriority), m_type()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAction_UI::~CAction_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CAction_UI::Init()
{
	//������
	CObject2D::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME[m_type])));

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAction_UI::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CAction_UI::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CAction_UI::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CAction_UI* CAction_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ACTION_TYPE type)
{
	CAction_UI* pAction_UI = new CAction_UI;

	if (pAction_UI == nullptr) { return nullptr; }

	pAction_UI->SetPos(pos);
	pAction_UI->SetSize(size);
	pAction_UI->SetColor(col);
	pAction_UI->m_type = type;

	pAction_UI->Init();

	return pAction_UI;
}
