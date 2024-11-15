//=============================================
//
//1�E�F�[�u����[wave_one.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_one.h"

const std::string CWave_One::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
const std::string CWave_One::WAVE_1_BLOCK_FILE = "data\\FILE\\block_000.txt";
const std::string CWave_One::WAVE_1_WALL_FILE = "data\\FILE\\wall_000.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CWave_One::CWave_One()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_One::~CWave_One()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_One::Init()
{
	CWave::LoadBlock(&WAVE_1_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_1_ENEMY_FILE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_One::Uninit()
{
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_One::Update()
{
	CWave::Update();
}
