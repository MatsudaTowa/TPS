//=============================================
//
//ゲームプレイヤー[game_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_H_ //これが定義されてないとき

#define _GAME_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//チュートリアルプレイヤークラス
//=============================================
class CGamePlayer :public CActivePlayer
{
public:
	CGamePlayer(int nPriority = PLAYER_PRIORITY);
	~CGamePlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif