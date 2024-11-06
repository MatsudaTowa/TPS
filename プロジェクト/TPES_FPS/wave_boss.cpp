//=============================================
//
//ボスウェーブ処理[wave_boss.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_boss.h"

const std::string CWave_Boss::WAVE_BOSS_ENEMY_FILE = "data\\FILE\\enemy_003.txt";
const std::string CWave_Boss::WAVE_BOSS_BLOCK_FILE = "data\\FILE\\block_003.txt";

CWave_Boss::CWave_Boss()
{
}

CWave_Boss::~CWave_Boss()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Boss::Init()
{
	CWave::LoadBlock(&WAVE_BOSS_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_BOSS_ENEMY_FILE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Boss::Uninit()
{
}

void CWave_Boss::Update()
{
}
