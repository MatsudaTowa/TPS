//=============================================
//
//ゲームスコア処理「game_scorer.cpp」
// Author松田永久
//
//=============================================
#include "game_score.h"

const float CGameScore::DIGIT_SHIFT = 40.0f;

const D3DXVECTOR3 CGameScore::BOX_POS = { 650.0f, 60.0f, 0.0f };
const D3DXVECTOR2 CGameScore::BOX_SIZE = { 230.0f, 80.0f };

const D3DXVECTOR3 CGameScore::NUM_POS = { 750.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::NUM_SIZE = { 20.0f, 30.0f };

//=============================================
//コンストラクタ
//=============================================
CGameScore::CGameScore(): m_pPlayerUIBox()
{
}

//=============================================
//デストラクタ
//=============================================
CGameScore::~CGameScore()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGameScore::Init()
{
	if (m_pPlayerUIBox == nullptr)
	{
		m_pPlayerUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_SCORE);
	}

	CScore::SetPos(NUM_POS);

	CScore::SetSize(NUM_SIZE);

	CScore::SetDigitShift(DIGIT_SHIFT);

	CScore::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGameScore::Uninit()
{
	if (m_pPlayerUIBox != nullptr)
	{
		m_pPlayerUIBox->Uninit();
		m_pPlayerUIBox = nullptr;
	}

	CScore::Uninit();
}

//=============================================
//更新
//=============================================
void CGameScore::Update()
{
	CScore::Update();
}
