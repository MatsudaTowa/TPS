//=============================================
//
//プレイヤーのステートパターン[player_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "player_test.h"
#include "ult.h"

//=============================================
//前方宣言
//=============================================
class CPlayer_test;

//=============================================
//キャラクターのステートクラス
//=============================================
class CPlayerState
{
public:
	virtual void Default(CPlayer_test* player);
	virtual void Ult(CPlayer_test* player);
};

//=============================================
//キャラクターの通常状態
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CPlayer_test* player)override;
};

//=============================================
//キャラクターのウルト状態
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CPlayer_test* player) override;
};

#endif // !_PLAYER_STATE_H
