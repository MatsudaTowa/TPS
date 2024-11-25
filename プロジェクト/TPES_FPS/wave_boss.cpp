//=============================================
//
//�{�X�E�F�[�u����[wave_boss.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_boss.h"

const std::string CWave_Boss::WAVE_BOSS_ENEMY_FILE = "data\\FILE\\enemy_003.txt";
const std::string CWave_Boss::WAVE_BOSS_BLOCK_FILE = "data\\FILE\\block_003.txt";
const std::string CWave_Boss::WAVE_BOSS_WALL_FILE = "data\\FILE\\wall_003.txt";
const std::string CWave_Boss::WAVE_BOSS_POINT_FILE = "data\\FILE\\boss_move_point.txt";

CMovePoint* CWave_Boss::m_pMovePoint[NUM_POINT] = {};
//=============================================
//�R���X�g���N�^
//=============================================
CWave_Boss::CWave_Boss()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_Boss::~CWave_Boss()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_Boss::Init()
{
	CWave::LoadBlock(&WAVE_BOSS_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_BOSS_ENEMY_FILE);
	LoadPoint(&WAVE_BOSS_POINT_FILE);
	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(900.0f, 0.0f, 900.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Boss::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_POINT; ++nCnt)
	{
		if (m_pMovePoint[nCnt] != nullptr)
		{
			m_pMovePoint[nCnt]->Uninit();
			m_pMovePoint[nCnt] = nullptr;
		}
	}
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Boss::Update()
{
	CWave::Update();
}

//=============================================
//�ʒu�擾
//=============================================
CMovePoint* CWave_Boss::GetMovePoint(int Idx)
{
	return m_pMovePoint[Idx];
}

//=============================================
//�|�C���g�̈ʒu�����[�h
//=============================================
void CWave_Boss::LoadPoint(const std::string* pFileName)
{
	char aDataSearch[CWave::TXT_MAX];
	char aEqual[CWave::TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumPoint; //�|�C���g�̐�
	int nCntPoint = 0;

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

		if (!strcmp(aDataSearch, "NUM_POINT"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumPoint);
		}
		if (!strcmp(aDataSearch, "POINTSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_POINTSET"))
				{
					//�ړ��|�C���g����
					m_pMovePoint[nCntPoint] = CMovePoint::Create(m_LoadPoint.pos);
					++nCntPoint;
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadPoint.pos.x,
						&m_LoadPoint.pos.y,
						&m_LoadPoint.pos.z);
				}
			}
		}
	}
}
