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
	void Chase(CBossEnemy* boss, CObject* obj);
	void MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss);
	bool PerformRaycast_Block(D3DXVECTOR3 vector, CBossEnemy* boss);
	bool PerformRaycast_Smoke(D3DXVECTOR3 vector, CBossEnemy* boss);
	bool ColisionBlock(int nCnt, const D3DXVECTOR3& startPos, const D3DXVECTOR3& direction);
	bool ColisionSmoke(int nCnt, const D3DXVECTOR3& startPos, const D3DXVECTOR3& direction);
	void DrawDebug();
private:
	bool m_bTargetPlayer; 
};

//=============================================
//敵の銃の攻撃のストラテジー
//=============================================
class CBossGunAttack : public CEnemyGunAttack
{
public:
	CBossGunAttack();
	~CBossGunAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;

private:
	static const int SHOT_STATE_FRAME = 180; //射撃フレーム

	int m_nStateChangeCnt;//ステート変更カウント
};

//=============================================
//突進攻撃のストラテジー
//=============================================
class CBossTackle
{
public:
	static const int TACKLE_DAMAGE = 30;

	CBossTackle();
	~CBossTackle();
	void Tackle(CBossEnemy* boss);
private:
	static const int STAY_FLAME = 120; //突進までの待機時間
	static const int TACKLE_FLAME = 150; //タックル時間
	void LookAtPlayer(CCharacter* character); //プレイヤーのほうを向かせる処理
	int m_StayCnt;
	int m_TackleCnt;
	bool m_isTackle;
};
#endif // !_ENEMY_BEHAVIOR_
