//=============================================
//
//�̗͕\���ulife_UI.cpp�v
// Author���c�i�v
//
//=============================================
#include "life_UI.h"
#include "manager.h"
#include "player.h"
//�����Ƃɂ��炷
const float CLife_UI::DIGIT_SHIFT = 18.0f;

const D3DXVECTOR3 CLife_UI::BOX_POS ={ 200.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::BOX_SIZE ={ 180.0f, 50.0f };

const D3DXVECTOR3 CLife_UI::GAUGE_POS = { 50.0f, 700.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::GAUGE_SIZE = { 300.0f,30.0f };

const D3DXVECTOR3 CLife_UI::NUM_POS = { 100.0f, 650.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::NUM_SIZE = { 10.0f, 18.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CLife_UI::CLife_UI() :m_nLife(0), m_pNumber(), m_pUIBox(), m_NumPos(), m_pGauge()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CLife_UI::~CLife_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CLife_UI::Init()
{
	m_NumPos = NUM_POS;

	//UI�̘g����
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE,{ 1.0f,1.0f,1.0f,1.0f },CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//�̗̓Q�[�W����
	if (m_pGauge == nullptr)
	{
		m_pGauge = CGauge_2D::Create(GAUGE_POS, GAUGE_SIZE, CGauge_2D::GAUGE2D_TYPE::GAUGE_TYPE_LIFE,{0.0f,1.0f,0.0f,1.0f});
	}

	//��������
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_NumPos, NUM_SIZE);
			//���W�����炷
			m_NumPos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CLife_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
	
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}
}

//=============================================
//�X�V
//=============================================
void CLife_UI::Update()
{
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Update();
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Update();
	}
}

//=============================================
//UI�ɐݒ�
//=============================================
void CLife_UI::SetLife_UI(int nLife)
{
	SetNumber(nLife);

	float gaugeWidth = (nLife * GAUGE_SIZE.x) / CPlayer::PLAYER_LIFE;

	m_pGauge->SetGauge({ gaugeWidth , m_pGauge->GetSize().y});

	if (nLife >= CPlayer::PLAYER_LIFE * 0.6f)
	{
		m_pGauge->SetColor({ 0.0f,1.0f,0.0f,1.0f });
	}
	else if (nLife >= CPlayer::PLAYER_LIFE * 0.3f && nLife < CPlayer::PLAYER_LIFE * 0.6f)
	{
		m_pGauge->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	}
	else if (nLife < CPlayer::PLAYER_LIFE * 0.3f)
	{
		m_pGauge->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}
}

//=============================================
//�����ݒ�
//=============================================
void CLife_UI::SetNumber(int nLife)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = nLife / nDigit % 10;

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
