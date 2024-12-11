//=============================================
//
//残弾数表示「ammo_UI.cpp」
// Author松田永久
//
//=============================================
#include "ammo_UI.h"
#include "manager.h"

//桁ごとにずらす
const float CAmmo_UI::DIGIT_SHIFT = 28.0f;
const D3DXVECTOR3 CAmmo_UI::BOX_POS = { 1080.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CAmmo_UI::BOX_SIZE = { 150.0f, 35.0f };

const D3DXVECTOR3 CAmmo_UI::NUM_POS = { 1000.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CAmmo_UI::NUM_SIZE = { 15.0f, 35.0f };

//=============================================
//コンストラクタ
//=============================================
CAmmo_UI::CAmmo_UI():m_nAmmo(),m_pos(),m_pNumber(), m_pUIBox()
{
}

//=============================================
//デストラクタ
//=============================================
CAmmo_UI::~CAmmo_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAmmo_UI::Init()
{
	//初期位置代入
	m_pos = NUM_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 0.0f,0.0f,0.0f,0.65f });
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, NUM_SIZE);
			//座標をずらす
			m_pos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CAmmo_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}

	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}
}

//=============================================
//更新
//=============================================
void CAmmo_UI::Update()
{
}

//=============================================
//UIに設定
//=============================================
void CAmmo_UI::SetAmmo_UI(int nAmmo)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nAmmo / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
