//=============================================
//
//プレイヤー[player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //これが定義されてないとき

#define _PLAYER_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"

//=============================================
//プレイヤークラス
//=============================================
class CPlayer:public CCharacter
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int PLAYER_PRIORITY = 8; //描画順

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//プレイヤー作成
	static CPlayer* Create(CPlayer* player);
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //スポーン位置
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //スポーン方向

	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ

	void DebugPos();	//デバッグ時位置情報表示
};
#endif