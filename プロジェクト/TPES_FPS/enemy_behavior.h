//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"

//=============================================
//�G�̍U���̃X�g���e�W�[
//=============================================
class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
		CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character) override;
};
#endif // !_ENEMY_BEHAVIOR_
