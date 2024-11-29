//=============================================
//
//ボスのステートパターン[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_

#include "character_state.h"
#include "boss_enemy.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//ボスのステートクラス
//=============================================
class CBossState
{
public:
	virtual void Chase(CBossEnemy* boss);
	virtual void Wandering(CBossEnemy* boss);
	virtual void Tackle(CBossEnemy* boss);
	virtual void DrawDebug();
};

//=============================================
//エネミーの追跡状態
//=============================================
class CChaseState : public CBossState
{
public:
	CChaseState();
	~CChaseState();
	virtual void Chase(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	static const int HP_LOW = 20;
	static const int PLAY_TACKLE_FLAME = 600; //タックルを実行するまでのフレーム
	int m_PlayTackleCnt; //タックルまでの計測用
};

//=============================================
//エネミーの徘徊状態
//=============================================
class CWanderingState : public CBossState
{
public:
	virtual void Wandering(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};

//=============================================
//エネミーのタックル状態
//=============================================
class CTackleState : public CBossState
{
public:
	virtual void Tackle(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};
#endif