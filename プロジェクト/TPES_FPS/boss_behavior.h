//=============================================
//
//ボスのストラテジーパターン[boss_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "enemy.h"

//=============================================
//敵の徘徊のストラテジー
//=============================================
class CBossWandering
{
public:
	CBossWandering();
	~CBossWandering();
	void Wandering(CEnemy* enemy);
private:
};

//=============================================
//敵の追従のストラテジー
//=============================================
class CBossChase
{
public:
	CBossChase();
	~CBossChase();
	void Chase(CEnemy* enemy);
private:

};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CBossAttack : public CEnemyAttack
{
public:
	CBossAttack();
	~CBossAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	static const int SHOT_STATE_FRAME = 180; //射撃フレーム

	int m_nStateChangeCnt;//ステート変更カウント
};
#endif // !_ENEMY_BEHAVIOR_
