//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_behavior.h"
//=============================================
//コンストラクタ
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//攻撃処理(プレイヤー)
//=============================================
void CPlayerAttack::Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
	CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character)
{
	pGun->m_nRateCnt++;
	if (pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
	{
		pGun->m_nRateCnt = 0;
		//弾発射
		pGun->ShotBullet(pos, move, size, nDamage, Allegiance, type);
	}
}