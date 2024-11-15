//=============================================
//
//3�E�F�[�u����[wave_three.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_three.h"

const std::string CWave_Three::WAVE_3_ENEMY_FILE = "data\\FILE\\enemy_002.txt";
const std::string CWave_Three::WAVE_3_BLOCK_FILE = "data\\FILE\\block_002.txt";
const std::string CWave_Three::WAVE_3_WALL_FILE = "data\\FILE\\wall_002.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CWave_Three::CWave_Three()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_Three::~CWave_Three()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_Three::Init()
{
	CWave::LoadBlock(&WAVE_3_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_3_ENEMY_FILE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Three::Uninit()
{
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Three::Update()
{
	CWave::Update();
}
