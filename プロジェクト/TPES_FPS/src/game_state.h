//=============================================
//
//ゲームのステートパターン[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

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
	* @brief ニュートラル処理
	* @param [in]ゲームプレイヤーポインタ
	*/
	void Normal(CGame* game) override;
};

/** @brief 状態処理クラス */
class CPause :public CGameState
{
public:
	~CPause()override;
	/**
	* @brief ポーズ状態処理
	* @param [in]ゲームポインタ
	*/
	void Pause(CGame* game) override;
private:
};

#endif // !_GAME_STATE_H_
