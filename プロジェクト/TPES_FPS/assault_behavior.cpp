//=============================================
//
//�A�T���g�e�̃X�g���e�W�[�p�^�[��[assault_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "assault_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CAssaultShot::CAssaultShot()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAssaultShot::~CAssaultShot()
{
}

//=============================================
//�A�T���g�e���ˏ���
//=============================================
void CAssaultShot::Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, 
CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun* gun)
{
	//���݂̒e���擾
	int nAmmo = gun->GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 60, nDamage, Allegiance, type);
		nAmmo--;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//�R���X�g���N�^
//=============================================
CAssaultReload::CAssaultReload()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAssaultReload::~CAssaultReload()
{
}

//=============================================
//�A�T���g�����[�h����
//=============================================
bool CAssaultReload::Reload(CGun* gun)
{
	bool bReload = true; //�����[�h�����ǂ���
	int nCnt = GetReloadCnt();
	
	nCnt++;

	if (nCnt >= CAssultRifle::DEFAULT_AR_RELOAD_FRAME)
	{
		nCnt = 0;
		//���݂̒e���擾
		int nAmmo = gun->GetAmmo();
		//�f�t�H���g�̃}�K�W���e�����
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		gun->SetAmmo(nAmmo);
		bReload = false;
	}

	SetReloadCnt(nCnt);
	return bReload;
}
