//=============================================
//
//1ウェーブ処理[wave_one.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_one.h"

const std::string CWave_One::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
const std::string CWave_One::WAVE_1_BLOCK_FILE = "data\\FILE\\block_000.txt";

CWave_One::CWave_One()
{
}

CWave_One::~CWave_One()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_One::Init()
{
	CWave::LoadBlock(&WAVE_1_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_1_ENEMY_FILE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_One::Uninit()
{
}

//=============================================
//更新
//=============================================
void CWave_One::Update()
{
}
