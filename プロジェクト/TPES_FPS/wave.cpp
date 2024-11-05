//=============================================
//
//�E�F�[�u����[wave.h]
//Auther Matsuda Towa
//
//=============================================
#include "wave.h"
#include "enemy_test.h"
#include "manager.h"
const std::string CWave::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
const std::string CWave::WAVE_2_ENEMY_FILE = "data\\FILE\\enemy_001.txt";
const std::string CWave::WAVE_3_ENEMY_FILE = "data\\FILE\\enemy_002.txt";
const std::string CWave::WAVE_BOSS_ENEMY_FILE = "data\\FILE\\enemy_003.txt";

const std::string CWave::WAVE_1_BLOCK_FILE = "data\\FILE\\block_000.txt";
const std::string CWave::WAVE_2_BLOCK_FILE = "data\\FILE\\block_001.txt";
const std::string CWave::WAVE_3_BLOCK_FILE = "data\\FILE\\block_002.txt";
const std::string CWave::WAVE_BOSS_BLOCK_FILE = "data\\FILE\\block_003.txt";
//=============================================
//�R���X�g���N�^
//=============================================
CWave::CWave():m_CurrentWave()
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
	m_CurrentWave = WAVE::NONE;
	//�E�F�[�u�ݒ�
	SetWave();
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
	if (CEnemy::m_NumEnemy <= 0)
	{
		SetWave();
	}
}

//=============================================
//�`��
//=============================================
void CWave::Draw()
{
}

//=============================================
//�E�F�[�u�ݒ�
//=============================================
void CWave::SetWave()
{
	switch (m_CurrentWave)
	{//���̃E�F�[�u�ɐ؂�ւ���
	case WAVE::NONE:
		m_CurrentWave = WAVE::ONE;
		LoadBlock(&WAVE_1_BLOCK_FILE);
		LoadEnemy(&WAVE_1_ENEMY_FILE);
		break;
	case WAVE::ONE:
		m_CurrentWave = WAVE::TWO;
		LoadBlock(&WAVE_2_BLOCK_FILE);
		LoadEnemy(&WAVE_2_ENEMY_FILE);
		break;
	case WAVE::TWO:
		m_CurrentWave = WAVE::THREE;
		LoadBlock(&WAVE_3_BLOCK_FILE);
		LoadEnemy(&WAVE_3_ENEMY_FILE);
		break;
	case WAVE::THREE:
		m_CurrentWave = WAVE::BOSS;
		LoadBlock(&WAVE_BOSS_BLOCK_FILE);
		LoadEnemy(&WAVE_BOSS_ENEMY_FILE);
		break;
	case WAVE::BOSS:
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
		break;
	default:
		break;
	}
}

//=============================================
//���݂̃E�F�[�u���擾
//=============================================
CWave::WAVE CWave::GetWave()
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
