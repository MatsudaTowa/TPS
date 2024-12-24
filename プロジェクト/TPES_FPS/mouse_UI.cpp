#include "mouse_UI.h"
#include "manager.h"

//=============================================
//�e�N�X�`���p�X
//=============================================
const std::string CMouse_UI::TEXTURE_NAME[CMouse_UI::MOUSE_MAX]
{
	"data\\TEXTURE\\mouseUI_L.png",
	"data\\TEXTURE\\mouseUI_R.png",
};

//=============================================
//�R���X�g���N�^
//=============================================
CMouse_UI::CMouse_UI(int nPriority):CObject2D(nPriority), m_type()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMouse_UI::~CMouse_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CMouse_UI::Init()
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
void CMouse_UI::Uninit()
{
	//�I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMouse_UI::Update()
{
	//�X�V
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CMouse_UI::Draw()
{
	//�`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CMouse_UI* CMouse_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, MOUSE_TYPE type)
{
	CMouse_UI* pMouse_UI = new CMouse_UI;

	if (pMouse_UI == nullptr) { return nullptr; }

	pMouse_UI->SetPos(pos);
	pMouse_UI->SetSize(size);
	pMouse_UI->SetColor(col);
	pMouse_UI->m_type = type;

	pMouse_UI->Init();

	return pMouse_UI;
}
