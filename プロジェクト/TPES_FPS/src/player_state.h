//=============================================
//
//プレイヤーのステートパターン[player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "ult.h"

//=============================================
//前方宣言
//=============================================
class CActivePlayer;

//=============================================
//キャラクターのステートクラス
//=============================================
class CPlayerState
{
public:
	virtual void Default(CActivePlayer* player);
	virtual void Ult(CActivePlayer* player);
	virtual void Avoidance(CActivePlayer* player);
	virtual void Blown(CActivePlayer* player);
};

//=============================================
//キャラクターの通常状態
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CActivePlayer* player)override;
};

//=============================================
//キャラクターのウルト状態
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CActivePlayer* player) override;
};

//=============================================
//キャラクターの回避状態
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	virtual void Avoidance(CActivePlayer* player) override;
};

//=============================================
//キャラクターの吹っ飛ばされ状態
//=============================================
class CBlownState : public CPlayerState
{
public:
	CBlownState();
	virtual void Blown(CActivePlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
