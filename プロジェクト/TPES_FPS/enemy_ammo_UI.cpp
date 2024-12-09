//=============================================
//
//�G�̎c�e���\���uenemy_ammo_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "enemy_ammo_UI.h"

//�����Ƃɂ��炷
const float CEnemy_Ammo_UI::DIGIT_SHIFT = 10.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_Ammo_UI::CEnemy_Ammo_UI() :m_nAmmo(), m_pos(), m_size() , m_pNumber()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_Ammo_UI::~CEnemy_Ammo_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy_Ammo_UI::Init()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_3D::Create(m_pos,m_size);
			//���W�����炷
			m_pos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_Ammo_UI::Uninit()
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
void CEnemy_Ammo_UI::Update()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->SetPos(m_pos);
			//���W�����炷
			m_pos.x -= DIGIT_SHIFT;
		}
	}
}

//=============================================
//�e���̐ݒ�
//=============================================
void CEnemy_Ammo_UI::SetAmmo_UI(int nAmmo)
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

//=============================================
//����
//=============================================
CEnemy_Ammo_UI* CEnemy_Ammo_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy_Ammo_UI* pAmmoUI = new CEnemy_Ammo_UI;
	
	if(pAmmoUI == nullptr) {return nullptr;}

	pAmmoUI->m_pos = pos;
	pAmmoUI->m_size = size;
	pAmmoUI->Init();

	return pAmmoUI;
}
