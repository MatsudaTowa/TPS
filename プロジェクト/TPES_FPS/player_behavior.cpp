//=============================================
//
//�v���C���[�̃X�g���e�W�[�p�^�[��[player_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_behavior.h"
//=============================================
//�R���X�g���N�^
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//�U������(�v���C���[)
//=============================================
void CPlayerAttack::Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
	CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character)
{
	pGun->m_nRateCnt++;
	if (pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
	{
		pGun->m_nRateCnt = 0;
		//�e����
		pGun->ShotBullet(pos, move, size, nDamage, Allegiance, type);
	}
}