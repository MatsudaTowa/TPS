//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyAttack::CEnemyAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyAttack::~CEnemyAttack()
{
}

//=============================================
//�U������(�G�l�~�[)
//=============================================
void CEnemyAttack::Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
	CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character)
{
	if (pGun->GetAmmo() > 0)
	{
		pGun->m_nRateCnt++;
		if (pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
		{
			pGun->m_nRateCnt = 0;
			//�e����
			pGun->ShotBullet(pos, move, size, nDamage, Allegiance, type);
		}
	}
	else
	{
		pGun->m_pReload->Reload(pGun);
	}

}