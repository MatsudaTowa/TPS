//=============================================
//
//�X���[�N�󋵕\���usmoke_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "smoke_UI.h"

//�����Ƃɂ��炷
const float CSmoke_UI::DIGIT_SHIFT = 35.0f;

const D3DXVECTOR3 CSmoke_UI::BOX_POS = { 1150.0f, 565.0f, 0.0f };
const D3DXVECTOR2 CSmoke_UI::BOX_SIZE = { 50.0f, 50.0f };

const D3DXVECTOR3 CSmoke_UI::ICON_POS = { 1150.0f,565.0f,0.0f };
const D3DXVECTOR2 CSmoke_UI::ICON_SIZE = { 40.0f, 40.0f };

const D3DXVECTOR3 CSmoke_UI::NUMBER_POS = { 1000.0f, 565.0f, 0.0f };
const D3DXVECTOR2 CSmoke_UI::NUMBER_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CSmoke_UI::KEY_UI_POS = { 1150.0f,600.0f,0.0f };
const D3DXVECTOR2 CSmoke_UI::KEY_UI_SIZE = { 18.0f, 18.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CSmoke_UI::CSmoke_UI():
m_SmokePos({0.0f,0.0f,0.0f}),	//�X���[�N�̈ʒu������
m_NumSmoke(0),					//�X���[�N�̐�������
m_pCurrentSmoke(),				//���݂̃X���[�N�̐��̃|�C���^������
m_pUIBox(),						//UI�̘g������
m_pIcon(),						//�A�C�R���̏�����
m_pkeyboard_UI()				//�L�[�{�[�h�̏�����
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmoke_UI::~CSmoke_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CSmoke_UI::Init(CPlayer* player)
{
	m_SmokePos = NUMBER_POS;

	//UI�̘g����
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//UI�̘g����
	if (m_pIcon == nullptr)
	{
		m_pIcon = CSmokeIcon::Create(ICON_POS, ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	//�L�[�{�[�hUI�̘g����
	if (m_pkeyboard_UI == nullptr)
	{
		m_pkeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CKeyboard_UI::KEY_Q);
	}

	//��������
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentSmoke[nCnt] == nullptr)
		{
			m_pCurrentSmoke[nCnt] = CNumber_2D::Create(m_SmokePos, NUMBER_SIZE);
			//���W�����炷
			m_SmokePos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmoke_UI::Uninit()
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
		if (m_pCurrentSmoke[nCnt] != nullptr)
		{
			m_pCurrentSmoke[nCnt]->Uninit();
			m_pCurrentSmoke[nCnt] = nullptr;
		}
	}

	delete this;
}

//=============================================
//�X�V
//=============================================
void CSmoke_UI::Update()
{
}

//=============================================
//���݂�UI�̐ݒ�
//=============================================
void CSmoke_UI::SetCurrentSmoke_UI(CPlayer* player)
{
	if (player->GetSmoke())
	{//�X���[�N���g���Ă�����
		m_pIcon->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	}
	else if (!player->GetSmoke())
	{//�X���[�N���g���Ă��Ȃ�������
		m_pIcon->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	}
}

//=============================================
//�����ݒ�
//=============================================
void CSmoke_UI::SetNumber(int nParcent)
{
}

//=============================================
//������Ԃ�
//=============================================
void CSmoke_UI::Reset()
{
}
