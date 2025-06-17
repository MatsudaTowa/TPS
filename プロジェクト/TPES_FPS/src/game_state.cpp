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

//=============================================
// デストラクタ
//=============================================
CPause::~CPause()
{
}

//=============================================
// ポーズ処理
//=============================================
void CPause::Pause(CGame* game)
{
	//オブジェクトのアップデートを止める
	game->UpdateObjectDecision(false);
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
