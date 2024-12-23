//=============================================
//
//�c�e���\���uammo_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "ammo_UI.h"
#include "manager.h"

//�����Ƃɂ��炷
const float CAmmo_UI::CURRENT_AMMO_DIGIT_SHIFT = 35.0f;
const float CAmmo_UI::DEFAULT_AMMO_DIGIT_SHIFT = 20.0f;

const D3DXVECTOR3 CAmmo_UI::BOX_POS = { 1070.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CAmmo_UI::BOX_SIZE = { 180.0f, 50.0f };

const D3DXVECTOR3 CAmmo_UI::CURRENT_AMMO_POS = { 1000.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CAmmo_UI::CURRENT_AMMO_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CAmmo_UI::DEFAULT_AMMO_POS = { 1065.0f, 670.0f, 0.0f };
const D3DXVECTOR2 CAmmo_UI::DEFAULT_AMMO_SIZE = { 10.0f, 20.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CAmmo_UI::CAmmo_UI():m_nDefaultAmmo(0), m_CurrentAmmoPos(), m_DefaultAmmoPos(), m_pCurrentAmmo(), m_pDefaultAmmo(), m_pUIBox()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAmmo_UI::~CAmmo_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CAmmo_UI::Init()
{
	//�����ʒu���
	m_CurrentAmmoPos = CURRENT_AMMO_POS;
	m_DefaultAmmoPos = DEFAULT_AMMO_POS;

	//UI�̘g����
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f },CPlayerUIBox::BOX_TYPE::BOX_TYPE_AMMO);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentAmmo[nCnt] == nullptr)
		{
			m_pCurrentAmmo[nCnt] = CNumber_2D::Create(m_CurrentAmmoPos, CURRENT_AMMO_SIZE);
			//���W�����炷
			m_CurrentAmmoPos.x -= CURRENT_AMMO_DIGIT_SHIFT;
		}

		if (m_pDefaultAmmo[nCnt] == nullptr)
		{
			m_pDefaultAmmo[nCnt] = CNumber_2D::Create(m_DefaultAmmoPos, DEFAULT_AMMO_SIZE);
			//���W�����炷
			m_DefaultAmmoPos.x -= DEFAULT_AMMO_DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAmmo_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentAmmo[nCnt] != nullptr)
		{
			m_pCurrentAmmo[nCnt]->Uninit();
			m_pCurrentAmmo[nCnt] = nullptr;
		}

		if (m_pDefaultAmmo[nCnt] != nullptr)
		{
			m_pDefaultAmmo[nCnt]->Uninit();
			m_pDefaultAmmo[nCnt] = nullptr;
		}
	}

	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	delete this;
}

//=============================================
//�X�V
//=============================================
void CAmmo_UI::Update()
{
}

//=============================================
//UI�ɐݒ�
//=============================================
void CAmmo_UI::SetCurrentAmmo_UI(int nAmmo)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = nAmmo / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		if (nAmmo < m_nDefaultAmmo * 0.3f)
		{//�e�����Ȃ��Ȃ�����ԐF��
			m_pCurrentAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_pCurrentAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================
//UI�ɐݒ�
//=============================================
void CAmmo_UI::SetDefaultAmmo_UI(int nAmmo)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//�f�t�H���g�e�����
	m_nDefaultAmmo = nAmmo;

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = nAmmo / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pDefaultAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
