//=============================================
//
//ゲーム処理[game.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //これが定義されてないとき

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"

//=============================================
// ゲームクラス
//=============================================
class CGame:public CScene
{
public:

	enum GAME_STATE
	{
		GAME_STATE_NORMAL = 0,
		GAME_STATE_MAX,
	};

	//読み込むときに必要なブロックの構造体
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数

	/**
	 * @brief コンストラクタ
	 */
	CGame();
	/**
	 * @brief デストラクタ
	 */
	~CGame() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief 描画
	 */
	void Draw() override;
	/**
	 * @brief 状態設定
	 * @param [in]状態
	 */
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	/**
	 * @brief ステート取得
	 * @return ステート
	 */
	static GAME_STATE&GetState();
	/**
	 * @brief プレイヤー取得
	 * @return プレイヤー
	 */
	CPlayer*GetPlayer();

	/**
	 * @brief ウェーブ取得
	 * @return ウェーブ
	 */
	static CWave*GetWave();

	/**
	 * @brief ウェーブ設定
	 * @param [in]wave
	 */
	static void SetWave(CWave::WAVE wave);

	/**
	 * @brief ウェーブ設定
	 * @param [in]ウェーブ
	 * @param [in]次のウェーブ
	 * @param [in]リザルトのスコアファイル
	 */
	static void SetWave(CWave::WAVE wave,CWave::WAVE next_wave,const char* ResultFile);
private:
	static const std::string BLOCK_FILE;	//エネミーのファイル

	static const int DELAY_FLAME = 60; //ディレイのフレーム数
	static const int DEATH_PENALTY = -50; //死んだときのペナルティ

	/**
	 * @brief 死亡ペナルティ計算
	 */
	void ApplyDeathPenalty();

	int m_nResultDelay; //リザルトへのディレイ
	static GAME_STATE m_GameState; //ゲームステート
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	CPlayer*m_pPlayer;
	static CWave* m_pWave;

	CWave::WAVE m_next_wave;
};
#endif