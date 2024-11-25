//=============================================
//
//3DTemplate[game.cpp]
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
#include "player_test.h"

const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//�v���C���[
CPlayer*CGame::m_pPlayer = nullptr;

//�E�F�[�u
CWave*CGame::m_pWave = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false), m_next_wave()
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�G�f�B�b�g���ĂȂ���ԂɕύX
	//�ǂݍ��ރu���b�N�̏�񏉊���
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	if (CEnemy::m_NumEnemy <= 0)
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
			if (m_nResultDelay > 60)
			{
				m_nResultDelay = 0;

				//���݂̃X�R�A�������o��
				m_pWave->WaveResult(&CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
			}
		}
	}

	if (pKeyboard->GetTrigger(DIK_TAB))
	{
		m_next_wave = CWave::WAVE::BOSS;

		SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Update();
	}
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetInstance()->GetCamera();

		pCamera->ResetCamera();
	}
	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();


#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG

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

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumBlock; //�u���b�N�̐�

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}
	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//�G�l�~�[����
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
