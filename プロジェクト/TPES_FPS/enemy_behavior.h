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
private:
	static const int MOVE_FRAME = 120; //移動フレーム

	int m_nStateChangeCnt;
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
	void GunAction(CGun* pGun, const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& size, int nDamage, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type);
private:
	static const int SHOT_FRAME = 180; //射撃フレーム

	int m_nStateChangeCnt;
};
#endif // !_ENEMY_BEHAVIOR_
