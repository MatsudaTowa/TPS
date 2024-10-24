//=============================================
//
//レティクル[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CReticle::CReticle(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CReticle::~CReticle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CReticle::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CReticle::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CReticle::Update()
{
	//親クラスの更新
	CObject3D::Update();
}

//=============================================
//描画
//=============================================
void CReticle::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CReticle* CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CReticle* pRaticle = nullptr;

	if (pRaticle == nullptr) 
	{
		return nullptr; 
	}

	CTexture* pTexture = CManager::GetTexture();

	pRaticle->SetPos(pos); //pos設定
	pRaticle->SetSize(size); //サイズ設定
	pRaticle->SetRot(rot);

	pRaticle->SetType(OBJECT_TYPE_RETICLE); //タイプ設定
	pRaticle->Init();

	return pRaticle;
}

//=============================================
//移動処理
//=============================================
void CReticle::Move()
{
	//マウスの情報取得
	CInputMouse* pMouse = CManager::GetMouse();
}
