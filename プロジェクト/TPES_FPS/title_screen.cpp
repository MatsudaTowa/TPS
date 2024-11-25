//=============================================
//
//3DTemplate[title_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "title_screen.h"
#include "manager.h"
#include "object.h"

//tex�p�X
const std::string CTitle_Screen::ROGO_TEXTURE_NAME = "data\\TEXTURE\\title_test.png";
const std::string CTitle_Screen::BUTTON_A_TEXTURE_NAME = "data\\TEXTURE\\title_test.png";
const std::string CTitle_Screen::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\title_test.png";

//=============================================
//�R���X�g���N�^
//=============================================
CTitle_Screen::CTitle_Screen(int nPriority):CObject2D(nPriority),m_UItype(CTitle_Screen::TITLE_UI::UI_NONE)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTitle_Screen::~CTitle_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CTitle_Screen::Init()
{

	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle_Screen::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTitle_Screen::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (m_UItype)
	{
	case CTitle_Screen::TITLE_UI::UI_TITLE_ROGO:
		BindTexture(pTexture->GetAddress(pTexture->Regist(&ROGO_TEXTURE_NAME)));
		break;
	case CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
		}
		break;
	default:
		break;
	}
}

//=============================================
//�`��
//=============================================
void CTitle_Screen::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CTitle_Screen* CTitle_Screen::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TITLE_UI type)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CTitle_Screen* pTitle_Screen = new CTitle_Screen;

	//null�Ȃ�null��Ԃ�
	if (pTitle_Screen == nullptr) {return nullptr;}

	pTitle_Screen->SetPos(pos); //pos�ݒ�

	pTitle_Screen->SetSize(size); //size�ݒ�

	pTitle_Screen->m_UItype = type;

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (pTitle_Screen->m_UItype)
	{
	case CTitle_Screen::TITLE_UI::UI_TITLE_ROGO:
		pTitle_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&ROGO_TEXTURE_NAME)));
		break;
	case CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{
			pTitle_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{
			pTitle_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
		}
		break;
	default:
		break;
	}

	pTitle_Screen->SetType(OBJECT_TYPE_TITLE); //�^�C�v�ݒ�

	pTitle_Screen->Init();

	return pTitle_Screen;
}
