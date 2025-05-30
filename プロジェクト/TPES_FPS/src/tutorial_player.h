//=============================================
//
//チュートリアルプレイヤー[tutorial_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_PLAYER_H_ //これが定義されてないとき

#define _TUTORIAL_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//チュートリアルプレイヤークラス
//=============================================
class CTutorialPlayer :public CActivePlayer
{
public:
	CTutorialPlayer(int nPriority = PLAYER_PRIORITY);
	~CTutorialPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif