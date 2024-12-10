//=============================================
//
//ゲージ管理[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge.h"

//=============================================
//コンストラクタ
//=============================================
CGauge::CGauge(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetGaugeVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();

	//頂点設定
	SetGaugeVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CGauge::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}


//=============================================
//ゲージ設定
//=============================================
void CGauge::SetGauge(D3DXVECTOR2 size)
{
	SetSize(size);
}

//=============================================
//生成
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col)
{
	CGauge* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos設定

	pGauge->SetSize(size); //size設定

	pGauge->SetColor(col);

	pGauge->m_type = type; //ゲージのタイプ設定

	pGauge->SetType(OBJECT_TYPE_GAUGE); //タイプ設定

	pGauge->Init();

	return pGauge;
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Life::CGauge_Life(int nPriority) :CGauge(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Life::Init()
{
	//親クラスの初期化
	CGauge::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Life::Uninit()
{
	//親クラスの終了
	CGauge::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Life::Update()
{
	//親クラスの更新
	CGauge::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Life::Draw()
{
	//親クラスの描画
	CGauge::Draw();
}

