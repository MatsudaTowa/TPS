//=============================================
//
//�E�F�[�u����[wave.h]
//Auther Matsuda Towa
//
//=============================================
#include "wave.h"
#include "manager.h"
#include "wave_one.h"
#include "wave_two.h"
#include "wave_three.h"
#include "wave_boss.h"
#include "wave_result.h"
#include "game_score.h"
#include "wave_score.h"
#include"player.h"
#include "wall.h"
#include "move_point.h"
#include "mask.h"
#include "gauge.h"

CWave::WAVE CWave::m_CurrentWave = WAVE::NONE;
CWave::WAVE CWave::m_next = WAVE::NONE;
const char* CWave::m_ResultFile = nullptr;
//�X�R�A
CScore* CWave::m_pScore = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CWave::CWave()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave::~CWave()
{
}

//=============================================
//������
//=============================================
HRESULT CWave::Init()
{
	CMask::Create();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave::Uninit()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CWave::Update()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
}

//=============================================
//�E�F�[�u�ݒ�
//=============================================
CWave* CWave::Create(WAVE wave)
{
	// �C���X�^���X����
	CWave* pWave = new CWave;

	// ��������
	switch (wave)
	{
	case WAVE::ONE: // �E�F�[�u1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //�E�F�[�u2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // �E�F�[�u3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //�E�F�[�uboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //�E�F�[�u���U���g

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	//�X�R�A������
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//�v���C���[����
			CPlayer::Create(CPlayer::PLAYER_SPAWN_POS, CPlayer::PLAYER_SPAWN_ROT, CPlayer::PLAYER_LIFE);
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//���̃V�[���̏�����
	pWave->Init();

	return pWave;
}

//=============================================
//�E�F�[�u�ݒ�
//=============================================
CWave* CWave::Create(WAVE wave, WAVE next_wave,const char* ResultFile)
{
	// �C���X�^���X����
	CWave* pWave = nullptr;

	m_next = next_wave;

	m_ResultFile = ResultFile;

	// ��������
	switch (wave)
	{
	case WAVE::RESULT: //�E�F�[�u���U���g

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	//�X�R�A������
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//�v���C���[����
			CPlayer::Create(D3DXVECTOR3(0.0f, 0.5f, -70.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
			CGauge_3D::Create(D3DXVECTOR3(0.0f, 0.5f, -70.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), CGauge_3D::GAUGE3D_TYPE::GAUGE_TYPE_STAMINA,{1.0f,1.0f,0.0f,1.0f});
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//���̃V�[���̏�����
	pWave->Init();

	return pWave;
}

//=============================================
//���݂̃E�F�[�u���擾
//=============================================
CWave::WAVE CWave::GetCurrentWave()
{
	return m_CurrentWave;
}

//=============================================
//�X�R�A�擾
//=============================================
CScore* CWave::GetScore()
{
	return m_pScore;
}

//=============================================
//�u���b�N�����[�h
//=============================================
void CWave::LoadBlock(const std::string* pFileName)
{
	//��������u���b�N���ǂݍ��ݗp
	int NumBlock = 0;

	//��������u���b�N���ǂݍ��ݗp
	LOAD_BLOCK Info[256];

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "rb");

	if (pFile != NULL)
	{
		//�G�̎g�p���Ă鐔�̓ǂݍ���
		fread(&NumBlock, sizeof(int), 1, pFile);

		//�G�̎g�p�����A�G�̓ǂݍ���
		fread(&Info[0], sizeof(LOAD_BLOCK), NumBlock, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < NumBlock; nCnt++)
	{
		CBlock::Create(Info[nCnt].type, Info[nCnt].pos, Info[nCnt].rot, 3, true);
	}
}

//=============================================
//�ǂ����[�h
//=============================================
void CWave::LoadWall(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumWall; //�ǂ̐�

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

		if (!strcmp(aDataSearch, "NUM_WALL"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumWall);
		}
		if (!strcmp(aDataSearch, "WALLSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_WALLSET"))
				{
					//�u���b�N����
					CWall::Create(m_LoadWall.pos, m_LoadWall.rot,m_LoadWall.size);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.pos.x,
						&m_LoadWall.pos.y,
						&m_LoadWall.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.rot.x,
						&m_LoadWall.rot.y,
						&m_LoadWall.rot.z);
				}
				else if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.size.x,
						&m_LoadWall.size.y,
						&m_LoadWall.size.z);
				}
			}
		}
	}
}

//=============================================
//�G�l�~�[�����[�h
//=============================================
void CWave::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumEnemy; //�G�l�~�[�̐�

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

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//�G�l�~�[����
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}


