//=============================================
//
//エネミーのステートパターン[enemy_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_STATE_H_
#define _ENEMY_STATE_H_

#include "character_state.h"
#include "enemy.h"

//=============================================
//前方宣言
//=============================================
class CEnemy;

//=============================================
//エネミーのステートクラス
//=============================================
class CEnemyState
{
public:
	virtual void Move(CEnemy* enemy);
};

//=============================================
//エネミーの移動状態(雑魚敵のみ) TODO:ならステートパターン組み換えよう
//=============================================
class CEnemyMoveState : public CEnemyState
{
public:
	virtual void Move(CEnemy* enemy);
};

#endif // !_CHARACTER_STATE_H
