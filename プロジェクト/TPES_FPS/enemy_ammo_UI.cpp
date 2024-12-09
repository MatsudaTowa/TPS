//=============================================
//
//敵の残弾数表示「enemy_ammo_UI.cpp」
// Author松田永久
//
//=============================================
#include "enemy_ammo_UI.h"

//桁ごとにずらす
const float CEnemy_Ammo_UI::DIGIT_SHIFT = 10.0f;

//=============================================
//コンストラクタ
//=============================================
CEnemy_Ammo_UI::CEnemy_Ammo_UI() :m_nAmmo(), m_pos(), m_size() , m_pNumber()
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Ammo_UI::~CEnemy_Ammo_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Ammo_UI::Init()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_3D::Create(m_pos,m_size);
			//座標をずらす
			m_pos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_Ammo_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
}

//=============================================
//更新
//=============================================
void CEnemy_Ammo_UI::Update()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->SetPos(m_pos);
			//座標をずらす
			m_pos.x -= DIGIT_SHIFT;
		}
	}
}

//=============================================
//弾数の設定
//=============================================
void CEnemy_Ammo_UI::SetAmmo_UI(int nAmmo)
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

//=============================================
//生成
//=============================================
CEnemy_Ammo_UI* CEnemy_Ammo_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy_Ammo_UI* pAmmoUI = new CEnemy_Ammo_UI;
	
	if(pAmmoUI == nullptr) {return nullptr;}

	pAmmoUI->m_pos = pos;
	pAmmoUI->m_size = size;
	pAmmoUI->Init();

	return pAmmoUI;
}
