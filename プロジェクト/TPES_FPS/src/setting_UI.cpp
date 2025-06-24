//=============================================
//
//�ݒ��UI�usetting_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "setting_UI.h"
#include "manager.h"

//�Q�[�W�̈ʒu
const D3DXVECTOR3 CSetting_UI::GAUGE_POS = { 450.0f, 300.0f, 0.0f };
//�Q�[�W�̃T�C�Y
const D3DXVECTOR2 CSetting_UI::GAUGE_SIZE = { 400.0f,60.0f };

//�ԍ��̈ʒu
const D3DXVECTOR3 CSetting_UI::NUM_POS = { 935.0f, 270.0f, 0.0f };
//�ԍ��̃T�C�Y
const D3DXVECTOR2 CSetting_UI::NUM_SIZE = { 17.0f, 25.0f };

//�����_�̈ʒu
const D3DXVECTOR3 CSetting_UI::DECIMAL_POINT_POS = { 882.0f, 285.0f, 0.0f };
//�����_�̃T�C�Y
const D3DXVECTOR2 CSetting_UI::DECIMAL_POINT__SIZE = { 2.5f, 2.5f };

//�����̈ʒu
const D3DXVECTOR3 CSetting_UI::TXT_POS = { 380.0f, 275.0f, 0.0f };
//�����̃T�C�Y
const D3DXVECTOR2 CSetting_UI::TXT_SIZE = { 85.0f, 45.0f };
//=============================================
//�R���X�g���N�^
//=============================================
CSetting_UI::CSetting_UI() :
m_pNumber(),			//�����̃|�C���^
m_pDecimalPoint(),		//�����_�̃|�C���^
m_NumPos(),				//�����̈ʒu
m_pGauge(),				//�Q�[�W�̃|�C���^
m_pTxtUI(),				//�e�L�X�g�|�C���^
m_pMask(nullptr)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSetting_UI::~CSetting_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CSetting_UI::Init()
{
	m_NumPos = NUM_POS;

	m_pMask = CMask::Create(new CPauseMask);

	if (m_pTxtUI == nullptr)
	{
		m_pTxtUI = CSensTxtUI::Create(TXT_POS, TXT_SIZE);
	}

	//�̗̓Q�[�W����
	if (m_pGauge == nullptr)
	{
		m_pGauge = CGauge_2D::Create(GAUGE_POS, GAUGE_SIZE, CGauge_2D::GAUGE2D_TYPE::GAUGE_TYPE_SENS, COLOR_WHITE);
	}

	//��������
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_NumPos, NUM_SIZE, new CSensNumber);
			//���W�����炷
			m_NumPos.x -= DIGIT_SHIFT;
		}
	}
	if (m_pDecimalPoint == nullptr)
	{
		m_pDecimalPoint = CDecimalPoint::Create(DECIMAL_POINT_POS,DECIMAL_POINT__SIZE,COLOR_WHITE);
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSetting_UI::Uninit()
{
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}

	if (m_pDecimalPoint != nullptr)
	{
		m_pDecimalPoint->Uninit();
		m_pDecimalPoint = nullptr;
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	if (m_pTxtUI != nullptr)
	{
		m_pTxtUI->Uninit();
		m_pTxtUI = nullptr;
	}

	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
	delete this;
}

//=============================================
//�X�V
//=============================================
void CSetting_UI::Update()
{
	if (m_pGauge != nullptr)
	{
		m_pGauge->Update();
	}
}

//=============================================
//���xUI
//=============================================
void CSetting_UI::SetSens_UI(float sens)
{
	SetNumber(sens);

	float gaugeWidth = (sens * GAUGE_SIZE.x) / FLOAT_ONE;

	m_pGauge->SetGauge({ gaugeWidth , m_pGauge->GetSize().y });
}

//=============================================
//���x�̐���
//=============================================
void CSetting_UI::SetNumber(float sens)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	sens *= 100;	//0.01�`1.00�𐮐��ɂ��邽�߂�

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = (int)sens / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, COLOR_WHITE);
	}
}
