//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_state.h"
#include "manager.h"
#include "enemy.h"
#include "wave.h"
#include "game.h"
#include "active_scene_state.h"

//=============================================
// �R���X�g���N�^
//=============================================
CGameNormal::CGameNormal()
{
}

//=============================================
// �ʏ폈��
//=============================================
void CGameNormal::Normal(CActiveScene* active_scene)
{
	CNormal::Normal(active_scene);

	CGame* pGame = dynamic_cast<CGame*>(active_scene);

	CWave::WAVE next_wave = pGame->GetNextWave();	//���̃E�F�[�u�ێ��p�ϐ�
	CWave* pWave = pGame->GetWave();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_P) && active_scene->GetPauseKey())
	{
		active_scene->ResetPauseCnt();
		active_scene->ChangeState(new CGamePause);
	}
	if (CEnemy::m_NumEnemy <= INT_ZERO)
	{//�G�����Ȃ��Ȃ�����E�F�[�u�J��
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
			int nResultDelay = pGame->GetResultDelay();
			nResultDelay++;
			if (nResultDelay > CGame::DELAY_FLAME)
			{
				nResultDelay = INT_ZERO;
				pGame->SetResultDelay(nResultDelay);

				//���񂾐��������X�R�A�}�C�i�X
				pGame->ApplyDeathPenalty();

				//���݂̃X�R�A�������o��
				pWave->WaveResult(CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				pGame->SetWave(CWave::WAVE::RESULT, next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
				pGame->SetNextWave(next_wave);
				return;
			}
			pGame->SetResultDelay(nResultDelay);
		}
	}

	if (pWave != nullptr)
	{
		pWave->Update();
	}

#ifdef _DEBUG
	CInputKeyboard* pKeyBoard = CManager::GetInstance()->GetKeyboard();

	if (pKeyBoard->GetTrigger(DIK_TAB))
	{
		next_wave = CWave::WAVE::BOSS;

		pGame->SetWave(CWave::WAVE::RESULT, next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

	if (pKeyBoard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG

	pGame->SetNextWave(next_wave);
}

//=============================================
// �|�[�Y����
//=============================================
void CGamePause::Pause(CActiveScene* active_scene)
{
	CPause::Pause(active_scene);
}

//=============================================
// �I������
//=============================================
void CGamePause::HandlePoseSelection(CActiveScene* active_scene)
{
	CPauseSelect* pSelect = GetSelectUI(GetSelect());
	if (typeid(*pSelect) == typeid(CPauseSelectContinue))
	{
		active_scene->ChangeState(new CGameNormal);
		return;
	}
	if (typeid(*pSelect) == typeid(CPauseSelectRetry))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_GAME);
		return;
	}
	if (typeid(*pSelect) == typeid(CPauseSelectQuit))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
		return;
	}
}

//=============================================
// �|�[�Y�L�����Z������
//=============================================
void CGamePause::CancelPause(CActiveScene* active_scene)
{
	active_scene->ChangeState(new CGameNormal);
}
