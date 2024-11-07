//=============================================
//
//ウェーブごとの結果[wave_result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_result.h"
#include "manager.h"
#include "game.h"
//スコア
CScore* CWave_Result::m_pScore = nullptr;
//=============================================
//コンストラクタ
//=============================================
CWave_Result::CWave_Result(): m_pScreen(),m_nScore()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Result::~CWave_Result()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Result::Init()
{
	//スコア初期化
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
//終了
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
//更新
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
//次のウェーブ設定
//=============================================
void CWave_Result::SetNextWave(CWave::WAVE wave)
{
	m_next = wave;
}

//=============================================
//スコアロード
//=============================================
void CWave_Result::LoadScore(const char* pFileName)
{
	//ファイルの読み込み
	FILE* pFile = fopen(pFileName, "rb");

	int nScore = 0; //返すスコア

	if (pFile != NULL)
	{
		//スコアの読み込み
		fread(&nScore, sizeof(int), 1, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{
		return;
	}

	m_nScore = nScore;

	m_pScore->AddScore(m_nScore);
}
