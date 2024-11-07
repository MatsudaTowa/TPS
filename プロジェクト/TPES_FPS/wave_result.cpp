//=============================================
//
//�E�F�[�u���Ƃ̌���[wave_result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_result.h"
#include "manager.h"
#include "game.h"
//�X�R�A
CScore* CWave_Result::m_pScore = nullptr;
//=============================================
//�R���X�g���N�^
//=============================================
CWave_Result::CWave_Result(): m_pScreen(),m_nScore()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_Result::~CWave_Result()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_Result::Init()
{
	//�X�R�A������
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;

		m_pScore->Init();
	}

	m_pScreen = nullptr;

	if (m_pScreen == nullptr)
	{
		m_pScreen = CWave_Result_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	LoadScore(m_ResultFile);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Result::Uninit()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	if (m_pScreen != nullptr)
	{
		m_pScreen->Uninit();
		m_pScreen = nullptr;
	}
}

//=============================================
//�X�V
//=============================================
void CWave_Result::Update()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
	if (m_pScreen != nullptr)
	{
		m_pScreen->Update();
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CGame::SetWave(m_next);
	}
}

//=============================================
//���̃E�F�[�u�ݒ�
//=============================================
void CWave_Result::SetNextWave(CWave::WAVE wave)
{
	m_next = wave;
}

//=============================================
//�X�R�A���[�h
//=============================================
void CWave_Result::LoadScore(const char* pFileName)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName, "rb");

	int nScore = 0; //�Ԃ��X�R�A

	if (pFile != NULL)
	{
		//�X�R�A�̓ǂݍ���
		fread(&nScore, sizeof(int), 1, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{
		return;
	}

	m_nScore = nScore;

	m_pScore->AddScore(m_nScore);
}
