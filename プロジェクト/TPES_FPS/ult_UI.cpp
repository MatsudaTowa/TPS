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

const D3DXVECTOR3 CUlt_UI::PARCENT_POS = {660.0f,700.0f,0.0f};
const D3DXVECTOR2 CUlt_UI::PARCENT_SIZE = { 10.0f, 18.0f };

//=============================================
// �R���X�g���N�^
//=============================================
CUlt_UI::CUlt_UI():m_PercentPos({0.0f,0.0f,0.0f}), m_pParcent(),m_pIcon()
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
HRESULT CUlt_UI::Init(CPlayer_test* player)
{
	m_PercentPos = PARCENT_POS;

	//UI�̘g����
	if (m_pIcon == nullptr)
	{
		float Addcolor = (1.0 - CUltIcon::START_COLOR.r) / player->m_pUlt->GetCoolTime();

		m_pIcon = CUltIcon::Create(ICON_POS, ICON_SIZE, Addcolor, CUltIcon::ULT_TYPE::ULT_TYPE_MEDIUM);
	}

	//��������
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pParcent[nCnt] == nullptr)
		{
			m_pParcent[nCnt] = CNumber_2D::Create(m_PercentPos, PARCENT_SIZE);
			//���W�����炷
			m_PercentPos.x -= PARCENT_DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CUlt_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pParcent[nCnt] != nullptr)
		{
			m_pParcent[nCnt]->Uninit();
			m_pParcent[nCnt] = nullptr;
		}
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
	if (m_pIcon != nullptr)
	{
		m_pIcon->Update();
	}
}

//=============================================
// UI�ݒ�
//=============================================
void CUlt_UI::SetCurrentUlt_UI(CPlayer_test* player)
{
	//�������o�����߂�float�ɃL���X�g
	int Parcent = ((float)player->m_pUlt->GetCoolTimeCnt() / (float)player->m_pUlt->GetCoolTime()) * 100;

	//�����ɐݒ�
	SetNumber(Parcent);
}

//=============================================
// �p�[�Z���g�ݒ�
//=============================================
void CUlt_UI::SetNumber(int nParcent)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = nParcent / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pParcent[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
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
