//=============================================
//
//�X�R�A�����uscorer.cpp�v
// Author���c�i�v
//
//=============================================
#include "score.h"
#include "manager.h"

const D3DXVECTOR3 CScore::NUM_POS = { 750.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CScore::NUM_SIZE = { 20.0f, 30.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CScore::CScore():m_nScore(0),m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_size({0.0f,0.0f})
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
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, m_size);
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
//�\���T�C�Y�擾
//=============================================
D3DXVECTOR2& CScore::GetSize()
{
	return m_size;
}

//=============================================
//���̍��W���炷�ϐ��擾
//=============================================
float& CScore::GetDigitShift()
{
	return m_DigitShift; 
}
