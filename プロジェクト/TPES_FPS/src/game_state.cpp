//=============================================
//
//ゲームのステートパターン[game_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_state.h"
#include "manager.h"
#include "enemy.h"
#include "wave.h"
#include "game.h"
#include "pause_select_continue.h"
#include "pause_select_retry.h"
#include "pause_select_quit.h"

//=============================================
// コンストラクタ
//=============================================
CNormal::CNormal()
{
	while(1)
	{
		int nCnt = ShowCursor(FALSE);
		if (nCnt > 0)
		{
			continue;
		}
		break;
	}
	ShowCursor(FALSE);
}

//=============================================
// 通常処理
//=============================================
void CNormal::Normal(CGame* game)
{
	//オブジェクトのアップデートを許可する
	game->UpdateObjectDecision(true);
	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(true);

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CWave::WAVE next_wave = game->GetNextWave();	//次のウェーブ保持用変数
	CWave* pWave = game->GetWave();

	if (CEnemy::m_NumEnemy <= INT_ZERO)
	{//敵がいなくなったらウェーブ遷移
		switch (CWave::GetCurrentWave())
		{
		case CWave::WAVE::ONE:
			next_wave = CWave::WAVE::TWO;
			break;
		case CWave::WAVE::TWO:
			next_wave = CWave::WAVE::THREE;
			break;
		case CWave::WAVE::THREE:
			next_wave = CWave::WAVE::BOSS;
			break;
		case CWave::WAVE::BOSS:
			next_wave = CWave::WAVE::NONE;
			break;
		case CWave::WAVE::NONE:
			break;
		default:
			break;
		}

		if (CWave::GetCurrentWave() != CWave::WAVE::RESULT)
		{
			int nResultDelay = game->GetResultDelay();
			nResultDelay++;
			if (nResultDelay > CGame::DELAY_FLAME)
			{
				nResultDelay = INT_ZERO;
				game->SetResultDelay(nResultDelay);

				//死んだ数分だけスコアマイナス
				game->ApplyDeathPenalty();

				//現在のスコアを書き出し
				pWave->WaveResult(CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				game->SetWave(CWave::WAVE::RESULT, next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
				game->SetNextWave(next_wave);
				return;
			}
			game->SetResultDelay(nResultDelay);
		}
	}

	if (pWave != nullptr)
	{
		pWave->Update();
	}

	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		game->ChangeState(new CPause);
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_TAB))
	{
		next_wave = CWave::WAVE::BOSS;

		game->SetWave(CWave::WAVE::RESULT, next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

	if (pKeyboard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG

	game->SetNextWave(next_wave);
}

//ポーズUI表示位置
const D3DXVECTOR3 CPause::POS[CPause::MAX]
{
	{SCREEN_WIDTH*HALF,200.0f,0.0f},
	{SCREEN_WIDTH * HALF,400.0f,0.0f},
	{SCREEN_WIDTH * HALF,600.0f,0.0f}
};

//=============================================
// コンストラクタ
//=============================================
CPause::CPause():
m_pSelect(),	//セレクトUIの数
m_pMask(nullptr)	//黒いマスク
{
	while(1)
	{
		int nCnt = ShowCursor(TRUE);
		if (nCnt < 0)
		{
			continue;
		}
		break;
	}

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			continue;
		}
		switch (i)
		{
		case CONTINUE:
			m_pSelect[i] = CPauseSelect::Create(POS[i],new CPauseSelectContinue);
			break;
		case RETRY:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectRetry);
			break;
		case QUIT:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectQuit);
			break;
		default:
			break;
		}

	}

	m_pMask = CMask::Create(new CPauseMask);
}

//=============================================
// デストラクタ
//=============================================
CPause::~CPause()
{
	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->Uninit();
			m_pSelect[i] = nullptr;
		}
	}
	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
}

//=============================================
// ポーズ処理
//=============================================
void CPause::Pause(CGame* game)
{
	//オブジェクトのアップデートを止める
	game->UpdateObjectDecision(false);

	//ポーズ関連のオブジェクトの更新は許可
	m_pMask->SetisActive(true);

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->SetisActive(true);
			m_pSelect[m_nSelect]->SetSelect(false);
		}
	}

	CInputKeyboard* pKeyBoard = CManager::GetInstance()->GetKeyboard();
	if (pKeyBoard->GetTrigger(DIK_S))
	{
		if (m_nSelect >= CPause::QUIT)
		{
			m_nSelect = CPause::CONTINUE;
			return;
		}
		++m_nSelect;
	}
	if (pKeyBoard->GetTrigger(DIK_W))
	{
		if (m_nSelect <= CPause::CONTINUE)
		{
			m_nSelect = CPause::QUIT;
			return;
		}
		--m_nSelect;
	}

	m_pSelect[m_nSelect]->SetSelect(true);

	if (pKeyBoard->GetTrigger(DIK_RETURN))
	{
		HandlePoseSelection(game);
	}

	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(false);

	//入力デバイス取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		game->ChangeState(new CNormal);
	}
}


//=============================================
// ポーズ処理
//=============================================
void CPause::HandlePoseSelection(CGame* game)
{
	if (typeid(*m_pSelect[m_nSelect]) == typeid(CPauseSelectContinue))
	{
		game->ChangeState(new CNormal);
		return;
	}
	if (typeid(*m_pSelect[m_nSelect]) == typeid(CPauseSelectRetry))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_GAME);
		return;
	}
	if (typeid(*m_pSelect[m_nSelect]) == typeid(CPauseSelectQuit))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
		return;
	}
}
