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
class CBossWandering : public CEnemyMove
{
public:
	CBossWandering();
	~CBossWandering() override;
	void Move(CCharacter* character)override;
private:
	static const int MOVE_FRAME = 60; //移動フレーム
	static const int RIGHT_PARCENT = 50; //右の確立
	static const int LEFT_PARCENT = 100; //左の確立

	int m_nRight;//左に行く確率
	int m_nLeft; //右に行く確率
	bool m_bRandom; //どっちに行くか決める
	int m_nStateChangeCnt; //ステート変更カウント
};

//=============================================
//敵の追従のストラテジー
//=============================================
class CBossChase : public CEnemyMove
{
public:
	CBossChase();
	~CBossChase() override;
	void Move(CCharacter* character)override;
private:
	static const int MOVE_FRAME = 60; //移動フレーム
	static const int RIGHT_PARCENT = 50; //右の確立
	static const int LEFT_PARCENT = 100; //左の確立

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
