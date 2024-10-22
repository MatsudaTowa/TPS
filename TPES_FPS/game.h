//=============================================
//
//3DTemplate[game.h]田所浩二は眠らない編
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //これが定義されてないとき

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include"block.h"

class CGame:public CScene
{
public:

	typedef enum
	{
		GAME_STATE_NORMAL = 0,
		GAME_STATE_MAX,
	}GAME_STATE;

	//読み込むときに必要なブロックの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	static const std::string BLOCK_FILE;	//エネミーのファイル
	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	static GAME_STATE&GetState();

	static CPlayer*GetPlayer();
private:
	int m_nResultDelay; //リザルトへのディレイ
	bool m_bEdit; //エディットしてるかどうか
	static GAME_STATE m_GameState; //ゲームステート
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	static CPlayer*m_pPlayer;

	void LoadBlock(const std::string* pFileName);
};
#endif