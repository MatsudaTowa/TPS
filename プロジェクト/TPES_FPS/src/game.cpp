//=============================================
//
//�Q�[��[game.cpp]
//Author Matsuda Towa
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
#include "active_player.h"

//�E�F�[�u
CWave* CGame::m_pWave = nullptr;
//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():
m_nResultDelay(INT_ZERO),	//���U���g�̑J�ڃf�B���C
m_next_wave(),				//���̃E�F�[�u�i�[�ϐ�
m_nPauseCnt(INT_ZERO),		//�|�[�Y�\�ϐ�
m_pState(nullptr)			//�X�e�[�g�|�C���^
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

	if (m_pState == nullptr)
	{
		m_pState = new CNormal;
	}

	if (m_pWave == nullptr)
	{
		m_pWave = new CWave;
		m_pWave->Init();
	}

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
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
	if (m_nPauseCnt <= PAUSE_POSSIBLE_FLAME)
	{
		++m_nPauseCnt;
	}
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Pause(this);
	}
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

		CActivePlayer* pPlayer = dynamic_cast<CActivePlayer*>(pObj);

		for (int nCnt = 0; nCnt < pPlayer->GetDeathCnt(); nCnt++)
		{
			CScore* pScore = CWave::GetScore();

			if (pScore->GetScore() > INT_ZERO)
			{
				pScore->AddScore(DEATH_PENALTY);

				if (pScore->GetScore() <= INT_ZERO)
				{//0�����������
					//�X�R�A0��
					pScore->SetScore(INT_ZERO);
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
//�X�e�[�g�ύX
//=============================================
void CGame::ChangeState(CGameState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
//�I�u�W�F�N�g�̍X�V���s��������
//=============================================
void CGame::UpdateObjectDecision(bool isActive)
{
	for (int i = 0; i < CObject::PRI_MAX; ++i)
	{
		for (int j = 0; j < CObject::MAX_OBJECT; ++j)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(i, j);	//�擪�擾

			if (pObj == nullptr)
			{
				continue;
			}

			if (pObj->GetisActive() != isActive)
			{
				pObj->SetisActive(isActive);
			}
		}
	}
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