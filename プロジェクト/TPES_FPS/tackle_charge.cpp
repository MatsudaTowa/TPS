//=============================================
//
//タックルチャージ中のエフェクト[tackle_charge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tackle_charge.h"
#include "manager.h"

//読み込むブロック情報のファイル
const std::string CTackleCharge::TEXTURE_NAME = "data\\TEXTURE\\ult_effect.png";

//=============================================
//コンストラクタ
//=============================================
CTackleCharge::CTackleCharge(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CTackleCharge::~CTackleCharge()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTackleCharge::Init()
{
	//テクスチャ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//テクスチャ設定
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); 

	//親クラスの初期化
	CBillboard::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTackleCharge::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CTackleCharge::Update()
{
	//親クラスの更新
	CBillboard::Update();
}

//=============================================
//描画
//=============================================
void CTackleCharge::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CTackleCharge* CTackleCharge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CTackleCharge* pTackleCharge = new CTackleCharge;

	if (pTackleCharge == nullptr) { return nullptr; }

	pTackleCharge->SetPos(pos);
	pTackleCharge->SetSize(size);
	pTackleCharge->SetColor(col);

	pTackleCharge->Init();

	return pTackleCharge;
}
