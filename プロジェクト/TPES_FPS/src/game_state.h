//=============================================
//
//ゲームのステートパターン[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"

//=============================================
//前方宣言
//=============================================
class CGame;

/** @brief ゲームのステートクラス */
class CGameState
{
public:
	CGameState() {};
	virtual ~CGameState() {};
	/**
	* @brief 通常処理(親では何もしない)
	* @param [in]ゲームポインタ
	*/
	virtual void Normal(CGame* game) {};

	/**
	* @brief ポーズ状態処理(親では何もしない)
	* @param [in]ゲームポインタ
	*/
	virtual void Pause(CGame* game) {};
};

/** @brief 通常クラス */
class CNormal :public CGameState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CNormal();
	/**
	* @brief ニュートラル処理
	* @param [in]ゲームプレイヤーポインタ
	*/
	void Normal(CGame* game) override;
};

/** @brief 状態処理クラス */
class CPause :public CGameState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CPause();
	/**
	 * @brief デストラクタ
	 */
	~CPause()override;
	/**
	* @brief ポーズ状態処理
	* @param [in]ゲームポインタ
	*/
	void Pause(CGame* game) override;
	/**
	 * @brief ポーズの選択されたUIの更新実行処理
	 * @param [in]ゲームシーンのポインタ
	 */
	void HandlePoseSelection(CGame* game);
private:
	enum PAUSE_SELECT
	{
		CONTINUE = 0,
		RETRY,
		QUIT,
		MAX
	};
	static const D3DXVECTOR3 POS[MAX];

	int m_nSelect;
	CMask* m_pMask;
	CPauseSelect* m_pSelect[MAX];
};

#endif // !_GAME_STATE_H_
