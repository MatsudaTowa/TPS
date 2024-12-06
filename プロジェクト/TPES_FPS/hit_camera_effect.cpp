//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.cpp」
// Author松田永久
//
//=============================================
#include "hit_camera_effect.h"
#include "manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CHitCameraEffect::m_pTextureTemp = nullptr;
const std::string CHitCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect002.png";

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffect::CHitCameraEffect(int nPriority): CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffect::~CHitCameraEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f);

	//サイズを代入
	SetSize(size);

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CHitCameraEffect::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffect::Update()
{
	//親クラスの終了
	CObject2D::Update();

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
}

//=============================================
//描画
//=============================================
void CHitCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CHitCameraEffect* CHitCameraEffect::Create(D3DXVECTOR3 pos)
{
	CHitCameraEffect* pHitCameraEffect = new CHitCameraEffect;
	//CObject *pObject = Getobject();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	if (pHitCameraEffect != nullptr)
	{
		pHitCameraEffect->SetPos(pos); //pos設定

		pHitCameraEffect->m_alpha = 0.8f;

		pHitCameraEffect->SetType(OBJECT_TYPE_FADE); //タイプ設定

		pHitCameraEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pHitCameraEffect->Init();
	}
	return pHitCameraEffect;
}

//=============================================
//アルファ値減算
//=============================================
void CHitCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
