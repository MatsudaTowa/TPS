//=============================================
//
//�`���[�g���A���X�N���[��[tutorial_screen.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial_screen.h"
#include "manager.h"
//tex�p�X
const std::string CTutorial_Screen::TXT_TEXTURE_NAME = "data\\TEXTURE\\tutorial.png";
const std::string CTutorial_Screen::BUTTON_A_TEXTURE_NAME = "data\\TEXTURE\\press_enter.png";
const std::string CTutorial_Screen::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\press_enter.png";

//=============================================
//�R���X�g���N�^
//=============================================
CTutorial_Screen::CTutorial_Screen(int nPriority) :CObject2D(nPriority), m_UItype(CTutorial_Screen::TUTORIAL_UI::UI_NONE)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTutorial_Screen::~CTutorial_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorial_Screen::Init()
{

	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorial_Screen::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTutorial_Screen::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (m_UItype)
	{
	case CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT:
		BindTexture(pTexture->GetAddress(pTexture->Regist(&TXT_TEXTURE_NAME)));
		break;
	case CTutorial_Screen::TUTORIAL_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{//pad�ڑ���
			BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{//pad�ڑ����ĂȂ�
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
void CTutorial_Screen::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CTutorial_Screen* CTutorial_Screen::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TUTORIAL_UI type)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CTutorial_Screen* pTutorialScreen = new CTutorial_Screen;

	//null�Ȃ�null��Ԃ�
	if (pTutorialScreen == nullptr) { return nullptr; }

	pTutorialScreen->SetPos(pos); //pos�ݒ�

	pTutorialScreen->SetSize(size); //size�ݒ�

	pTutorialScreen->m_UItype = type;

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (pTutorialScreen->m_UItype)
	{
	case CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT:
		pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TXT_TEXTURE_NAME)));
		break;
	case CTutorial_Screen::TUTORIAL_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{
			pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{
			pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
		}
		break;
	default:
		break;
	}

	pTutorialScreen->SetType(OBJECT_TYPE_TITLE); //�^�C�v�ݒ�

	pTutorialScreen->Init();

	return pTutorialScreen;
}
