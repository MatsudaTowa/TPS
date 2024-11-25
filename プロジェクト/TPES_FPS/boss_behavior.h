//=============================================
//
//ボスのストラテジーパターン[boss_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "boss_enemy.h"
#include "move_point.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//敵の徘徊のストラテジー
//=============================================
class CBossWandering
{
public:
	//止まってるフレーム数
	static const int STOP_FRAME = 30;
	CBossWandering();
	~CBossWandering();
	void Wandering(CBossEnemy* boss);
	void StopCnt();
	void PickNextMovePoint(CMovePoint* pMovePoint);
	void DrawDebug();
private:
	int m_MoveIdx; //移動先の番号
	int m_StopCnt; //止まってるカウント
	bool m_isMove; //動くかどうか
};

//=============================================
//敵の追従のストラテジー
//=============================================
class CBossChase
{
public:
	CBossChase();
	~CBossChase();
	void Chase(CBossEnemy* boss);
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
