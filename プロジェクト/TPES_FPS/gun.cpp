//=============================================
//
//銃[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"

//=============================================
//コンストラクタ
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate()
{
}

//=============================================
//デストラクタ
//=============================================
CGun::~CGun()
{
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

//=============================================
//コンストラクタ
//=============================================
CAssultRifle::CAssultRifle(): m_nReloadCnt()
{
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

	m_nReloadCnt = 0;

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
	//現在の弾数取得
	int nAmmo = GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 300, nDamage, Allegiance, type);
		nAmmo--;
	}
	SetAmmo(nAmmo);
}

//=============================================
//リロード処理
//=============================================
bool CAssultRifle::Reload()
{
	bool bReload = true; //リロード中かどうか
	m_nReloadCnt++;
	if (m_nReloadCnt >= CAssultRifle::DEFAULT_AR_RELOAD_FRAME)
	{
		m_nReloadCnt = 0;
		//現在の弾数取得
		int nAmmo = GetAmmo();
		//デフォルトのマガジン弾数代入
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		SetAmmo(nAmmo);
		bReload = false;
	}
	return bReload;
}
