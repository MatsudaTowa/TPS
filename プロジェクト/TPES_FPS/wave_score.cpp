//=============================================
//
//ウェーブスコア処理「wave_scorer.h」
// Author松田永久
//
//=============================================
#include "wave_score.h"

//数字の表示位置
const D3DXVECTOR3 CWaveScore::NUM_POS = { 850.0f ,SCREEN_HEIGHT * 0.5f,0.0f };
//数字の表示サイズ
const D3DXVECTOR2 CWaveScore::NUM_SIZE = { 40.0f, 50.0f };
//=============================================
//コンストラクタ
//=============================================
CWaveScore::CWaveScore()
{
}

//=============================================
//デストラクタ
//=============================================
CWaveScore::~CWaveScore()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWaveScore::Init()
{
	CScore::SetPos(NUM_POS);
	CScore::SetSize(NUM_SIZE);
	CScore::SetDigitShift(DIGIT_SHIFT);
	CScore::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWaveScore::Uninit()
{
	CScore::Uninit();
}

//=============================================
//更新
//=============================================
void CWaveScore::Update()
{
	CScore::Update();
}
