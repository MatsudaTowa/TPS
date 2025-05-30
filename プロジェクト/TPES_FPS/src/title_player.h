//=============================================
//
//タイトルプレイヤー[title_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_PLAYER_H_ //これが定義されてないとき

#define _TITLE_PLAYER_H_
#include "main.h"
#include "player.h"

//=============================================
//タイトルプレイヤークラス
//=============================================
class CTitlePlayer :public CPlayer
{
public:
	CTitlePlayer(int nPriority = PLAYER_PRIORITY);
	~CTitlePlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif