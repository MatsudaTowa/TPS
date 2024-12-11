//=============================================
//
//�X�R�A�����uscorer.cpp�v
// Author���c�i�v
//
//=============================================
#include "score.h"
#include "manager.h"

const D3DXVECTOR3 CScore::BOX_POS = { 1070.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CScore::BOX_SIZE = { 190.0f, 45.0f };

const D3DXVECTOR3 CScore::NUM_POS = { 100.0f, 650.0f, 0.0f };
const D3DXVECTOR2 CScore::NUM_SIZE = { 8.0f, 18.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CScore::CScore():m_nScore(0),m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)), m_pPlayerUIBox()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		m_pNumber[nCnt] = nullptr;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CScore::~CScore()
{
}

//=============================================
//������
//=============================================
HRESULT CScore::Init()
{
	if (m_pPlayerUIBox == nullptr)
	{
		//m_pPlayerUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE,{1.0f,1.0f,1.0f,1.0f}, CPlayerUIBox::BOX_TYPE::BOX_TYPE_SCORE);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
			//���W�����炷
			m_pos.x -= m_DigitShift;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CScore::Uninit()
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
void CScore::Update()
{
	SetScore(m_nScore);
}

//=============================================
//�`��
//=============================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================
//�X�R�A�����o��
//=============================================
void CScore::ExportScore(const std::string* pFileName)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "wb");

	if (pFile != NULL)
	{
		fwrite(&m_nScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//=============================================
//�X�R�A���Z�b�g
//=============================================
void CScore::Reset()
{
	m_nScore = 0;
}

//=============================================
//�X�R�A�ݒ�
//=============================================
void CScore::SetScore(int nScore)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = m_nScore / nDigit % 10;

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
//�\�����W�擾
//=============================================
D3DXVECTOR3& CScore::GetPos()
{
	return m_pos;
}

//=============================================
//���̍��W���炷�ϐ��擾
//=============================================
float& CScore::GetDigitShift()
{
	return m_DigitShift; 
}
