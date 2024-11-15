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
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Boss::Uninit()
{
	CWave::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Boss::Update()
{
	CWave::Update();
}
