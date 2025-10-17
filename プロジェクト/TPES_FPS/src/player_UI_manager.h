//=============================================
//
//プレイヤーUIマネージャー[player_UI_maneger.h]
//Auther MatsudaTowa
//
//=============================================

#ifndef _PLAYER_UI_MANAGER_H_	//これが定義されてないとき
#define _PLAYER_UI_MANAGER_H_	//二重マクロ防止

//ヘッダーのインクルード
#include "active_player.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "gun_icon.h"
#include "gauge.h"
#include "smoke_UI.h"
#include "blink_UI.h"
#include "reload_UI.h"

/** @brief My 名前空間 */
/** @brief ゲームマネージャークラス */
class CPlayerUIManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	CPlayerUIManager();

	/**
	* @brief デストラクタ
	*/
	~CPlayerUIManager();

	/**
	* @brief 終了
	*/
	void Uninit();

	/**
	* @brief 自分自身のインスタンスを生成し取得
	*/
	static CPlayerUIManager* GetInstance()
	{
		//静的インスタンス
		static CPlayerUIManager instance;
		return &instance;
	}

	/**
	* @brief UIを生成
	* @param [in]プレイヤー
	*/
	void CreateUI(CActivePlayer* player);

	/**
	* @brief UIを設定
	* @param [in]プレイヤー
	*/
	void SetUI(CActivePlayer* player);

	/**
	 * @brief 弾数UI取得
	 * @return 弾数UI
	 */
	CAmmo_UI* GetAmmoUI()
	{
		return m_pAmmoUI;
	}

	/**
	 * @brief ライフUI取得
	 * @return ライフUI
	 */
	CLife_UI* GetLifeUI()
	{
		return m_pLifeUI;
	}

	/**
	 * @brief ウルトUI取得
	 * @return ウルト
	 */
	CUlt_UI* GetUltUI()
	{
		return m_pUltUI;
	}

	/**
	 * @brief スモークUI取得
	 * @return スモークUI
	 */
	CSmoke_UI* GetSmokeUI()
	{
		return m_pSmokeUI;
	}

	/**
	 * @brief ブリンクUI取得
	 * @return ブリンクUI
	 */
	CBlink_UI* GetBlinkUI()
	{
		return m_pBlinkUI;
	}

	/**
	 * @brief リロードUI取得
	 * @return リロード
	 */
	CReload_UI* GetReloadUI()
	{
		return m_pReloadUI;
	}

	/**
	 * @brief 銃のアイコン取得
	 * @return 
	 */
	CGunIcon* GetGunIcon()
	{
		return m_pGunIcon;
	}

	/**
	 * @brief 弾数UI取得
	 * @param [in]弾数UI
	 */
	void SetAmmoUI(CAmmo_UI* pAmmoUI)
	{
		m_pAmmoUI = pAmmoUI;
	}

	/**
	 * @brief ライフUI取得
	 * @param [in]ライフUI
	 */
	void SetLifeUI(CLife_UI* pLifeUI)
	{
		m_pLifeUI = pLifeUI;
	}

	/**
	 * @brief ウルトUI取得
	 * @param [in]ウルト
	 */
	void SetUltUI(CUlt_UI* pUltUI)
	{
		m_pUltUI = pUltUI;
	}

	/**
	 * @brief スモークUI取得
	 * @param [in]スモークUI
	 */
	void SetSmokeUI(CSmoke_UI* pSmokeUI)
	{
		m_pSmokeUI = pSmokeUI;
	}

	/**
	 * @brief ブリンクUI取得
	 * @param [in]ブリンクUI
	 */
	void SetBlinkUI(CBlink_UI* pBlinkUI)
	{
		m_pBlinkUI = pBlinkUI;
	}

	/**
	 * @brief リロードUI取得
	 * @param [in]リロード
	 */
	void SetReloadUI(CReload_UI* pReloadUI)
	{
		m_pReloadUI = pReloadUI;
	}

	/**
	 * @brief 銃のアイコン取得
	 * @param [in]アイコン
	 */
	void SetGunIcon(CGunIcon* pGunIcon)
	{
		m_pGunIcon = pGunIcon;
	}
private:
	static const D3DXVECTOR3 GUN_UI_POS;//銃のUIの位置
	static const D3DXVECTOR2 GUN_UI_SIZE;//銃のUIのサイズ

	CAmmo_UI* m_pAmmoUI;	//残弾UI

	CLife_UI* m_pLifeUI;	//体力UI

	CUlt_UI* m_pUltUI;		//ウルトUI

	CSmoke_UI* m_pSmokeUI;	//スモークUI

	CBlink_UI* m_pBlinkUI;	//ブリンクUI

	CReload_UI* m_pReloadUI;	//リロードUI

	CGunIcon* m_pGunIcon;	//銃のアイコン
};

#endif