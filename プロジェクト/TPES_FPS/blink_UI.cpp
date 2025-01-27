//=============================================
//
//�u�����N�\���ublink_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "blink_UI.h"

//�����Ƃɂ��炷
const float CBlink_UI::DIGIT_SHIFT = 35.0f;

const D3DXVECTOR3 CBlink_UI::BOX_POS = { 470.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CBlink_UI::BOX_SIZE = { 50.0f, 50.0f };

const D3DXVECTOR3 CBlink_UI::ICON_POS = { 470.0f,665.0f,0.0f };
const D3DXVECTOR2 CBlink_UI::ICON_SIZE = { 40.0f, 40.0f };

const D3DXVECTOR3 CBlink_UI::NUMBER_POS = { 1000.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CBlink_UI::NUMBER_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CBlink_UI::KEY_UI_POS = { 470.0f,700.0f,0.0f };
const D3DXVECTOR2 CBlink_UI::KEY_UI_SIZE = { 40.0f, 20.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CBlink_UI::CBlink_UI():
m_BlinkUIPos({ 0.0f,0.0f,0.0f }),	//�u�����N��UI�ʒu������
m_NumBlink(0),					//�u�����N�̐�������
m_pCurrentBlink(),				//���݂̃u�����N�̐��̃|�C���^������
m_pUIBox(),						//UI�̘g������
m_pIcon(),						//�A�C�R���̏�����
m_pkeyboard_UI()				//�L�[�{�[�h�̏�����
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBlink_UI::~CBlink_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CBlink_UI::Init(CPlayer* player)
{
	m_BlinkUIPos = NUMBER_POS;

	//UI�̘g����
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//UI�̘g����
	if (m_pIcon == nullptr)
	{
		m_pIcon = CBlinkIcon::Create(ICON_POS, ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	//�L�[�{�[�hUI�̘g����
	if (m_pkeyboard_UI == nullptr)
	{
		m_pkeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CKeyboard_UI::KEY_LSHIFT);
	}

	//��������
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentBlink[nCnt] == nullptr)
		{
			m_pCurrentBlink[nCnt] = CNumber_2D::Create(m_BlinkUIPos, NUMBER_SIZE);
			//���W�����炷
			m_BlinkUIPos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlink_UI::Uninit()
{
	//UI�̘g�j��
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	//�L�[�{�[�hUI�̃A�C�R���j��
	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	//UI�̃A�C�R���j��
	if (m_pkeyboard_UI != nullptr)
	{
		m_pkeyboard_UI->Uninit();
		m_pkeyboard_UI = nullptr;
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//�����j��
		if (m_pCurrentBlink[nCnt] != nullptr)
		{
			m_pCurrentBlink[nCnt]->Uninit();
			m_pCurrentBlink[nCnt] = nullptr;
		}
	}

	delete this;
}

//=============================================
//�X�V
//=============================================
void CBlink_UI::Update()
{
}

//=============================================
//���݂̃u�����N��ԑ��
//=============================================
void CBlink_UI::SetCurrentBlink_UI(CPlayer* player)
{
	//if (player->GetSmoke())
	//{//�X���[�N���g���Ă�����
	//	m_pIcon->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	//}
	//else if (!player->GetSmoke())
	//{//�X���[�N���g���Ă��Ȃ�������
	//	m_pIcon->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//}
}

//=============================================
//����u�����N�ł��邩���
//=============================================
void CBlink_UI::SetNumber(int nParcent)
{
}

//=============================================
//���Z�b�g
//=============================================
void CBlink_UI::Reset()
{
}
