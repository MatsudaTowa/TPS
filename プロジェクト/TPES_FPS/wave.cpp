//=============================================
//
//�E�F�[�u����[wave.h]
//Auther Matsuda Towa
//
//=============================================
#include "wave.h"
#include "enemy_test.h"
#include "manager.h"
#include "wave_one.h"
#include "wave_two.h"
#include "wave_three.h"
#include "wave_boss.h"
#include "wave_result.h"

CWave::WAVE CWave::m_CurrentWave = WAVE::NONE;
CWave::WAVE CWave::m_next = WAVE::NONE;
const char* CWave::m_ResultFile = nullptr;

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
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CWave::Update()
{
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
		pWave = new CWave_Boss;
		break;
	default:
		break;
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
	CWave* pWave = new CWave;

	m_next = next_wave;

	m_ResultFile = ResultFile;

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
//�u���b�N�����[�h
//=============================================
void CWave::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[��]�ǂݍ��ݗp
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
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
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

void CWave::SetWaveScore(int nScore)
{
	m_nScore = nScore;
}

