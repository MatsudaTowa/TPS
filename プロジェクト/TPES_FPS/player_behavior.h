//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CPlayerAttack : public CAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
		CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character) override;
};
#endif // !_ENEMY_BEHAVIOR_
