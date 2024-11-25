//=============================================
//
//ボスのストラテジーパターン[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CBossWandering::CBossWandering()
{
}

//=============================================
//デストラクタ
//=============================================
CBossWandering::~CBossWandering()
{
}

//=============================================
//徘徊
//=============================================
void CBossWandering::Wandering(CEnemy* enemy)
{
}

//=============================================
//コンストラクタ
//=============================================
CBossChase::CBossChase()
{
}

//=============================================
//デストラクタ
//=============================================
CBossChase::~CBossChase()
{
}

//=============================================
//追跡
//=============================================
void CBossChase::Chase(CEnemy* enemy)
{
}

//=============================================
//コンストラクタ
//=============================================
CBossAttack::CBossAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CBossAttack::~CBossAttack()
{
}

//=============================================
//攻撃
//=============================================
void CBossAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	//if (m_nStateChangeCnt < SHOT_STATE_FRAME)
	//{
	//	CEnemyAttack::Attack(Allegiance, type, character);
	//	++m_nStateChangeCnt;
	//}
	//if (m_nStateChangeCnt >= SHOT_STATE_FRAME)
	//{
	//	m_nStateChangeCnt = 0;
	//	//移動状態に切り替え
	//	character->ChangeState(new CMoveState);
	//}
}
