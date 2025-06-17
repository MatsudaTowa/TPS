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

//=============================================
// �ʏ폈��
//=============================================
void CNormal::Normal(CGame* game)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g��������
	game->UpdateObjectDecision(true);
	//�J������
	CManager::GetInstance()->GetCamera()->SetActive(true);

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CWave::WAVE next_wave = game->GetNextWave();	//���̃E�F�[�u�ێ��p�ϐ�
	CWave* pWave = game->GetWave();

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
			int nResultDelay = game->GetResultDelay();
			nResultDelay++;
			if (nResultDelay > CGame::DELAY_FLAME)
			{
				nResultDelay = INT_ZERO;
				game->SetResultDelay(nResultDelay);

				//���񂾐��������X�R�A�}�C�i�X
				game->ApplyDeathPenalty();

				//���݂̃X�R�A�������o��
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
// �f�X�g���N�^
//=============================================
CPause::~CPause()
{
}

//=============================================
// �|�[�Y����
//=============================================
void CPause::Pause(CGame* game)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g���~�߂�
	game->UpdateObjectDecision(false);
	//�J������
	CManager::GetInstance()->GetCamera()->SetActive(false);

	//���̓f�o�C�X�擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		game->ChangeState(new CNormal);
	}
}
