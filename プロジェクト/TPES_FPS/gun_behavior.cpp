//=============================================
//
//�e�̃X�g���e�W�[�p�^�[��[gun_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CShot::CShot()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CShot::~CShot()
{
}

//=============================================
//�e���ˏ���
//=============================================
void CShot::Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* gun)
{
	//���݂̒e���擾
	int nAmmo = gun->GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 60, nDamage, Allegiance, type);
		--nAmmo;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//�R���X�g���N�^
//=============================================
CReload::CReload():m_nReloadCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CReload::~CReload()
{
}

//=============================================
//�J�E���g�擾
//=============================================
int& CReload::GetReloadCnt()
{
	return m_nReloadCnt;
}
