//=============================================
//
//1ウェーブ処理[wave_one.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_one.h"
#include "dash_effect.h"
#include "ult_effect.h"

const std::string CWave_One::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
const std::string CWave_One::WAVE_1_BLOCK_FILE = "data\\FILE\\block_data000.bin";
const std::string CWave_One::WAVE_1_WALL_FILE = "data\\FILE\\wall_000.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_One::CWave_One()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_One::~CWave_One()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_One::Init()
{
	CWave::Init();
	CWave::LoadBlock(&WAVE_1_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_1_ENEMY_FILE);
	CWave::LoadWall(&WAVE_1_WALL_FILE);
	//地面生成
	CField::Create(VEC3_RESET_ZERO, CWave::NORMAL_FIELD_SIZE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_One::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_One::Update()
{
	CWave::Update();
}
