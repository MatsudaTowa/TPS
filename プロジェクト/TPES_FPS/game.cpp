//=============================================
//
//�Q�[��[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "dash_effect.h"
#include "player.h"

//�v���C���[
CPlayer*CGame::m_pPlayer = nullptr;

//�E�F�[�u
CWave*CGame::m_pWave = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():
m_nResultDelay(INT_ZERO),	//���U���g�̑J�ڃf�B���C
m_next_wave()				//���̃E�F�[�u�i�[�ϐ�
{
	//�ǂݍ��ރu���b�N�̏�񏉊���
	m_LoadBlock.pos = VEC3_RESET_ZERO;
	m_LoadBlock.rot = VEC3_RESET_ZERO;
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//�f�X�g���N�^
//=============================================
CGame::~CGame()
{
}

//=============================================
//������
//=============================================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	if (m_pWave == nullptr)
	{
		m_pWave = new CWave;
		m_pWave->Init();
	}

	//�v���C���[����
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
	m_GameState = GAME_STATE_NORMAL;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		m_pWave = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	if (CEnemy::m_NumEnemy <= INT_ZERO)
	{//�G�����Ȃ��Ȃ�����E�F�[�u�J��
		switch (CWave::GetCurrentWave())
		{
		case CWave::WAVE::ONE:
			m_next_wave = CWave::WAVE::TWO;
			break;
		case CWave::WAVE::TWO:
			m_next_wave = CWave::WAVE::THREE;
			break;
		case CWave::WAVE::THREE:
			m_next_wave = CWave::WAVE::BOSS;
			break;
		case CWave::WAVE::BOSS:
			m_next_wave = CWave::WAVE::NONE;
			break;
		case CWave::WAVE::NONE:
			break;
		default:
			break;
		}

		if (CWave::GetCurrentWave() != CWave::WAVE::RESULT)
		{
			m_nResultDelay++;
			if (m_nResultDelay > DELAY_FLAME)
			{
				m_nResultDelay = INT_ZERO;

				//���񂾐��������X�R�A�}�C�i�X
				ApplyDeathPenalty();

				//���݂̃X�R�A�������o��
				m_pWave->WaveResult(&CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
			}
		}
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Update();
	}
	
#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_TAB))
	{
		m_next_wave = CWave::WAVE::BOSS;

		SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

	if (pKeyboard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG
}

//=============================================
//���񂾐������X�R�A�}�C�i�X
//=============================================
void CGame::ApplyDeathPenalty()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();
			
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ�������
			//�v���C���[��T��������
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		for (int nCnt = 0; nCnt < pPlayer->GetDeathCnt(); nCnt++)
		{
			CScore* pScore = CWave::GetScore();

			if (pScore->m_nScore > INT_ZERO)
			{
				pScore->AddScore(DEATH_PENALTY);

				if (pScore->m_nScore <= INT_ZERO)
				{//0�����������
					//�X�R�A0��
					pScore->m_nScore = INT_ZERO;
				}
			}
		}
	}
}

//=============================================
//�`��
//=============================================
void CGame::Draw()
{
}

//=============================================
//�v���C���[�擾
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//=============================================
//�E�F�[�u�擾
//=============================================
CWave* CGame::GetWave()
{
	return m_pWave;
}

//=============================================
//�E�F�[�u�ݒ�
//=============================================
void CGame::SetWave(CWave::WAVE wave)
{
	//�E�F�[�u�I��
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//�E�F�[�u�؂�ւ�
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave);
	}
}

//=============================================
//�E�F�[�u�ݒ�
//=============================================
void CGame::SetWave(CWave::WAVE wave, CWave::WAVE next_wave,const char* ResultFile)
{
	//�E�F�[�u�I��
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//�E�F�[�u�؂�ւ�
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave, next_wave, ResultFile);
	}
}

//=============================================
//�Q�[���̏�Ԏ擾
//=============================================
CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}