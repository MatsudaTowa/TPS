//=============================================
//
//�X�R�A�����uscorer.cpp�v
// Author���c�i�v
//
//=============================================
#include "score.h"
#include "manager.h"

//�����Ƃɂ��炷
const float CScore::DIGIT_SHIFT = 50.0f;
const float CScore::DEBUG_DIGIT_SHIFT = 120.0f;

int CScore::m_nSaveScore = 0; 

//=============================================
//�R���X�g���N�^
//=============================================
CScore::CScore():m_nScore(0),m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f))
{//�C�j�V�����C�U�[�Ń����o�ϐ�������

	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene == CScene::MODE::MODE_GAME)
	{
		//�����ʒu���
		m_pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);
	}
	else if (pScene == CScene::MODE::MODE_RESULT)
	{
		//�����ʒu���
		m_pos = D3DXVECTOR3(1140.0f, 460.0f, 0.0f);
	}

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
			//���݂̃V�[�����擾
			CScene::MODE pScene = CScene::GetSceneMode();
			if (pScene == CScene::MODE::MODE_GAME)
			{
				m_pNumber[nCnt] = CNumber::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
				//���W�����炷
				m_pos.x -= DIGIT_SHIFT;
			}
			else if (pScene == CScene::MODE::MODE_RESULT)
			{
				m_pNumber[nCnt] = CNumber::Create(m_pos, D3DXVECTOR2(70.0f, 90.0f));
				//���W�����炷
				m_pos.x -= DEBUG_DIGIT_SHIFT;
			}
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

int CScore::GetScore()
{
	return m_nSaveScore;
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
