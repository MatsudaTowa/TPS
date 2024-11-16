//=============================================
//
//2�E�F�[�u����[wave_two.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_two.h"

const std::string CWave_Two::WAVE_2_ENEMY_FILE = "data\\FILE\\enemy_001.txt";
const std::string CWave_Two::WAVE_2_BLOCK_FILE = "data\\FILE\\block_001.txt";
const std::string CWave_Two::WAVE_2_WALL_FILE = "data\\FILE\\wall_001.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CWave_Two::CWave_Two()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_Two::~CWave_Two()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_Two::Init()
{
	CWave::LoadBlock(&WAVE_2_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_2_ENEMY_FILE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Two::Uninit()
{
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Two::Update()
{
	CWave::Update();
}
