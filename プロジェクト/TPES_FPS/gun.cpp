//=============================================
//
//銃[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
//=============================================
//コンストラクタ
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate(), m_nRateCnt(0)
{
	m_pShot = nullptr;
	m_pReload = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CGun::~CGun()
{
	if (m_pShot != nullptr)
	{
		delete m_pShot;
	}
	if (m_pReload != nullptr)
	{
		delete m_pReload;
	}
}

//=============================================
//弾数取得
//=============================================
int& CGun::GetAmmo()
{
	return m_Ammo;
}

//=============================================
//レベル取得
//=============================================
int& CGun::GetLv()
{
	return m_Lv;
}

//=============================================
//リロードフレーム取得
//=============================================
int& CGun::GetReloadFrame()
{
	return m_ReloadFrame;
}

//=============================================
//発射レート取得
//=============================================
int& CGun::GetFireRate()
{
	return m_FireRate;
}

//弾のスピード
const float CAssultRifle::DEFAULT_AR_BULLET_SPEED = 15.0f;

//=============================================
//コンストラクタ
//=============================================
CAssultRifle::CAssultRifle()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CAssaultShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CAssaultReload;
	}
}

//=============================================
//デストラクタ
//=============================================
CAssultRifle::~CAssultRifle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAssultRifle::Init()
{
	//現在の弾数取得
	int nAmmo = GetAmmo();
	//現在のレベル取得
	int nLv = GetLv();
	//現在のリロードフレーム取得
	int nReloadFrame = GetReloadFrame();
	//現在の発射レート取得
	int nFireRate = GetFireRate();

	//デフォルトのマガジン弾数代入
	nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
	//初期レベル代入
	nLv = 1;
	//デフォルトのリロードフレーム代入
	nReloadFrame = CAssultRifle::DEFAULT_AR_RELOAD_FRAME;
	//デフォルトの発射レート代入
	nFireRate = CAssultRifle::DEFAULT_AR_FIRE_RATE;

	//各メンバー変数に代入
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);

	return S_OK;
}

//=============================================
//更新
//=============================================
void CAssultRifle::Uninit()
{
}

//=============================================
//弾発射処理
//=============================================
void CAssultRifle::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type)
{
	if (m_pShot != nullptr)
	{
		m_pShot->Shot(pos, move, size, nDamage, Allegiance, type, this);
	}
}

//=============================================
//リロード処理
//=============================================
bool CAssultRifle::Reload()
{
	bool bReload = true; //リロード中かどうか
	if (m_pReload != nullptr)
	{
		bReload = m_pReload->Reload(this);
	}
	return bReload;
}
