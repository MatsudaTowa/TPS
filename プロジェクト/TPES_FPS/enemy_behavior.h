//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CEnemyMove();
	~CEnemyMove() override;
	void Move(CCharacter* character)override;
	void SetMoveVec(D3DXVECTOR3 move_vec)
	{
		m_move_vec = move_vec;
	}
private:
	D3DXVECTOR3 m_move_vec;
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //プレイヤーのほうを向かせる処理

private:
};
#endif // !_ENEMY_BEHAVIOR_
