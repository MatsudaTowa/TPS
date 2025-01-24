//=============================================
//
//ult�󋵕\���uult_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "ult_UI.h"
#include "ult.h"

//�����Ƃɂ��炷
const float CUlt_UI::PARCENT_DIGIT_SHIFT = 18.0f;

const D3DXVECTOR3 CUlt_UI::ICON_POS = { SCREEN_WIDTH * 0.5f,660.0f,0.0f };
const D3DXVECTOR2 CUlt_UI::ICON_SIZE = { 70.0f, 70.0f };

const D3DXVECTOR3 CUlt_UI::KEY_UI_POS = { SCREEN_WIDTH * 0.5f,700.0f,0.0f};
const D3DXVECTOR2 CUlt_UI::KEY_UI_SIZE = { 18.0f, 18.0f };

//=============================================
// �R���X�g���N�^
//=============================================
CUlt_UI::CUlt_UI():m_PercentPos({0.0f,0.0f,0.0f}), m_pKeyboard_UI(),m_pIcon()
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CUlt_UI::~CUlt_UI()
{
}

//=============================================
// ������
//=============================================
HRESULT CUlt_UI::Init(CPlayer* player)
{
	//UI�̘g����
	if (m_pIcon == nullptr)
	{
		float Addcolor = (1.0 - CUltIcon::START_COLOR.r) / player->m_pUlt->GetCoolTime();

		m_pIcon = CUltIcon::Create(ICON_POS, ICON_SIZE, Addcolor, CUltIcon::ULT_TYPE::ULT_TYPE_MEDIUM);
	}

	if (m_pKeyboard_UI == nullptr)
	{
		m_pKeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, {1.0f,1.0f,1.0f,1.0f},CKeyboard_UI::KEY_X);
	}
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CUlt_UI::Uninit()
{
	if (m_pKeyboard_UI != nullptr)
	{
		m_pKeyboard_UI->Uninit();
		m_pKeyboard_UI = nullptr;
	}

	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	delete this;
}

//=============================================
// �X�V
//=============================================
void CUlt_UI::Update()
{
	if (m_pKeyboard_UI != nullptr)
	{
		m_pKeyboard_UI->Update();
	}

	if (m_pIcon != nullptr)
	{
		m_pIcon->Update();
	}
}

//=============================================
// UI�ݒ�
//=============================================
void CUlt_UI::SetCurrentUlt_UI(CPlayer* player)
{
	//�������o�����߂�float�ɃL���X�g
	int Parcent = ((float)player->m_pUlt->GetCoolTimeCnt() / (float)player->m_pUlt->GetCoolTime()) * 100;
}

//=============================================
// ���Z�b�g�֐�(ult���g��ꂽ�Ƃ��ɌĂ΂��)
//=============================================
void CUlt_UI::Reset()
{
	//�e�N���X�̃��Z�b�g�֐����ĂԂ���
	//�A�C�R���̃��Z�b�g����
	m_pIcon->Reset();
}
