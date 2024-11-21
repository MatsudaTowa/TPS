//=============================================
//
//ノーマルエネミーのストラテジーパターン[normal_enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_BEHAVIOR_
#define _NORMAL_ENEMY_BEHAVIOR_
#include "enemy_behavior.h"
#include "enemy.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CNormalMove : public CEnemyMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CNormalMove();
	~CNormalMove() override;
	void Move(CCharacter* character)override;
private:
	void NextMove_X(CCharacter* character);
	static const int MOVE_FRAME = 60; //移動フレーム
	static const int RIGHT_PARCENT = 50; //右の確立
	static const int LEFT_PARCENT = 100; //左の確立

	int m_nRight;//左に行く確率
	int m_nLeft; //右に行く確率
	bool m_bRandom; //どっちに行くか決める
	int m_nStateChangeCnt; //ステート変更カウント
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CNormalAttack : public CEnemyAttack
{
public:
	CNormalAttack();
	~CNormalAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	static const int SHOT_STATE_FRAME = 180; //射撃フレーム

	int m_nStateChangeCnt;//ステート変更カウント
};

#endif // !_ENEMY_BEHAVIOR_
