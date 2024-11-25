//=============================================
//
//�E�F�[�u���Ƃ̌���[wave_result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_result.h"
#include "manager.h"
#include "game.h"

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
	if (m_pScreen != nullptr)
	{
		m_pScreen->Uninit();
		m_pScreen = nullptr;
	}
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Result::Update()
{
	if (m_pScreen != nullptr)
	{
		m_pScreen->Update();
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (m_next != WAVE::NONE)
		{
			CGame::SetWave(m_next);
		}
		else
		{
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
		}
	}
	CWave::Update();
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
