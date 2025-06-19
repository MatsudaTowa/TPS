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
m_next_wave()				//���̃E�F�[�u�i�[�ϐ�
{
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

	CActiveScene::Init();

	ChangeState(new CGameNormal);

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	CActiveScene::Uninit();

	CManager::GetInstance()->GetSound()->StopSound();

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
	CActiveScene::Update();
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