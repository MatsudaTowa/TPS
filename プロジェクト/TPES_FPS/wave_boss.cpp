//=============================================
//
//ボスウェーブ処理[wave_boss.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_boss.h"
#include "move_point.h"

const std::string CWave_Boss::WAVE_BOSS_ENEMY_FILE = "data\\FILE\\enemy_003.txt";
const std::string CWave_Boss::WAVE_BOSS_BLOCK_FILE = "data\\FILE\\block_003.txt";
const std::string CWave_Boss::WAVE_BOSS_WALL_FILE = "data\\FILE\\wall_003.txt";
const std::string CWave_Boss::WAVE_BOSS_POINT_FILE = "data\\FILE\\boss_move_point.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Boss::CWave_Boss()
{
}

//=============================================
//デストラクタ
//=============================================
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
	CWave::LoadPoint(&WAVE_BOSS_POINT_FILE);
	//地面生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(900.0f, 0.0f, 900.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Boss::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Boss::Update()
{
	CWave::Update();
}
