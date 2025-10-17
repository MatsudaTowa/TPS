//=============================================
//
//プレイヤーUIマネージャー[player_UI_maneger.cpp]
//Auther MatsudaTowa
//
//=============================================
#include "player_UI_manager.h"

//銃のUIの位置
const D3DXVECTOR3 CPlayerUIManager::GUN_UI_POS = { 1150.0f, 665.0f, 0.0f };

//銃のUIのサイズ
const D3DXVECTOR2 CPlayerUIManager::GUN_UI_SIZE = { 70.0f,30.0f };
//=============================================
// コンストラクタ
//=============================================
CPlayerUIManager::CPlayerUIManager():
	m_pAmmoUI(nullptr),				//弾数UI
	m_pBlinkUI(nullptr),			//ブリンクUI
	m_pGunIcon(nullptr),			//銃のアイコン
	m_pLifeUI(nullptr),				//体力UI
	m_pReloadUI(nullptr),			//リロードUI
	m_pSmokeUI(nullptr),			//スモークUI
	m_pUltUI(nullptr)				//ウルトUI
{
}

//=============================================
// デストラクタ
//=============================================
CPlayerUIManager::~CPlayerUIManager()
{
}

//=============================================
// 終了
//=============================================
void CPlayerUIManager::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->Uninit();
		m_pBlinkUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pUltUI->Uninit();
		m_pUltUI = nullptr;
	}
	if (m_pGunIcon != nullptr)
	{
		m_pGunIcon->Uninit();
		m_pGunIcon = nullptr;
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->Uninit();
		m_pSmokeUI = nullptr;
	}
	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Uninit();
		m_pReloadUI = nullptr;
	}
}

//=============================================
// UIの生成
//=============================================
void CPlayerUIManager::CreateUI(CActivePlayer* player)
{
	if (m_pGunIcon == nullptr)
	{
		m_pGunIcon = CGunIcon::Create(GUN_UI_POS, GUN_UI_SIZE, COLOR_WHITE, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
	}
	//残弾数初期化
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();

		m_pAmmoUI->SetDefaultAmmo_UI(player->GetGun()->GetAmmo());
	}
	//体力UI初期化
	if (m_pLifeUI == nullptr)
	{
		m_pLifeUI = new CLife_UI;

		m_pLifeUI->Init();
	}
	//ブリンクUI初期化
	if (m_pBlinkUI == nullptr)
	{
		m_pBlinkUI = new CBlink_UI;

		m_pBlinkUI->Init();
	}
	//ウルトUI初期化
	if (m_pUltUI == nullptr)
	{
		m_pUltUI = new CUlt_UI;

		m_pUltUI->Init(player);
	}

	if (m_pSmokeUI == nullptr)
	{
		m_pSmokeUI = new CSmoke_UI;
		m_pSmokeUI->Init(player);
	}
}

//=============================================
// UI設定
//=============================================
void CPlayerUIManager::SetUI(CActivePlayer* player)
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetCurrentAmmo_UI(player->GetGun()->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(player->GetLife());
	}

	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->SetCurrentBlink_UI(player);
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->SetCurrentSmoke_UI(player);
	}
}
