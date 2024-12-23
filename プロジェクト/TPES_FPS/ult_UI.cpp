//=============================================
//
//ult状況表示「ult_UI.cpp」
// Author松田永久
//
//=============================================
#include "ult_UI.h"
#include "ult.h"

//桁ごとにずらす
const float CUlt_UI::PARCENT_DIGIT_SHIFT = 18.0f;

const D3DXVECTOR3 CUlt_UI::ICON_POS = { SCREEN_WIDTH * 0.5f,660.0f,0.0f };
const D3DXVECTOR2 CUlt_UI::ICON_SIZE = { 70.0f, 70.0f };

const D3DXVECTOR3 CUlt_UI::PARCENT_POS = {660.0f,700.0f,0.0f};
const D3DXVECTOR2 CUlt_UI::PARCENT_SIZE = { 10.0f, 18.0f };

//=============================================
// コンストラクタ
//=============================================
CUlt_UI::CUlt_UI():m_PercentPos({0.0f,0.0f,0.0f}), m_pParcent(),m_pIcon()
{
}

//=============================================
// デストラクタ
//=============================================
CUlt_UI::~CUlt_UI()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CUlt_UI::Init(CPlayer_test* player)
{
	m_PercentPos = PARCENT_POS;

	//UIの枠生成
	if (m_pIcon == nullptr)
	{
		float Addcolor = (1.0 - CUltIcon::START_COLOR.r) / player->m_pUlt->GetCoolTime();

		m_pIcon = CUltIcon::Create(ICON_POS, ICON_SIZE, Addcolor, CUltIcon::ULT_TYPE::ULT_TYPE_MEDIUM);
	}

	//数字生成
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pParcent[nCnt] == nullptr)
		{
			m_pParcent[nCnt] = CNumber_2D::Create(m_PercentPos, PARCENT_SIZE);
			//座標をずらす
			m_PercentPos.x -= PARCENT_DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CUlt_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pParcent[nCnt] != nullptr)
		{
			m_pParcent[nCnt]->Uninit();
			m_pParcent[nCnt] = nullptr;
		}
	}

	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	delete this;
}

//=============================================
// 更新
//=============================================
void CUlt_UI::Update()
{
	if (m_pIcon != nullptr)
	{
		m_pIcon->Update();
	}
}

//=============================================
// UI設定
//=============================================
void CUlt_UI::SetCurrentUlt_UI(CPlayer_test* player)
{
	//割合を出すためにfloatにキャスト
	int Parcent = ((float)player->m_pUlt->GetCoolTimeCnt() / (float)player->m_pUlt->GetCoolTime()) * 100;

	//数字に設定
	SetNumber(Parcent);
}

//=============================================
// パーセント設定
//=============================================
void CUlt_UI::SetNumber(int nParcent)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nParcent / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pParcent[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================
// リセット関数(ultが使われたときに呼ばれる)
//=============================================
void CUlt_UI::Reset()
{
	//各クラスのリセット関数を呼ぶだけ
	//アイコンのリセット処理
	m_pIcon->Reset();
}
