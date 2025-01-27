//=============================================
//
//�L�[�{�[�hUI�̕\�L[keyboard_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "keyboard_UI.h"
#include "manager.h"

//=============================================
//�e�N�X�`���p�X
//=============================================
const std::string CKeyboard_UI::TEXTURE_NAME[CKeyboard_UI::KEY_MAX]
{
	"data\\TEXTURE\\keyboard_W.png",
	"data\\TEXTURE\\keyboard_A.png",
	"data\\TEXTURE\\keyboard_S.png",
	"data\\TEXTURE\\keyboard_D.png",
	"data\\TEXTURE\\keyboard_Q.png",
	"data\\TEXTURE\\keyboard_X.png",
	"data\\TEXTURE\\keyboard_R.png",
	"data\\TEXTURE\\keyboard_LSHIFT.png",
};

//=============================================
//�R���X�g���N�^
//=============================================
CKeyboard_UI::CKeyboard_UI(int nPriority):CObject2D(nPriority),m_type()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CKeyboard_UI::~CKeyboard_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CKeyboard_UI::Init()
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
void CKeyboard_UI::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CKeyboard_UI::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CKeyboard_UI::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CKeyboard_UI* CKeyboard_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, KEY_TYPE key)
{
	CKeyboard_UI* pKeyboard_UI = new CKeyboard_UI;

	if (pKeyboard_UI == nullptr) { return nullptr; }

	pKeyboard_UI->SetPos(pos);
	pKeyboard_UI->SetSize(size);
	pKeyboard_UI->SetColor(col);
	pKeyboard_UI->m_type = key;

	pKeyboard_UI->Init();

	return pKeyboard_UI;
}
