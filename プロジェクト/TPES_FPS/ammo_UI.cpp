//=============================================
//
//�c�e���\���uammo_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "ammo_UI.h"
#include "manager.h"

//�����Ƃɂ��炷
const float CAmmo_UI::DIGIT_SHIFT = 50.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CAmmo_UI::CAmmo_UI():m_nAmmo(),m_pos(),m_pNumber()
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
	m_pos = D3DXVECTOR3(1100.0f, 650.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
			//���W�����炷
			m_pos.x -= DIGIT_SHIFT;
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
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
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
void CAmmo_UI::SetAmmo_UI(int nAmmo)
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

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
