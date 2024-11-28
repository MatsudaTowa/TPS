//=============================================
//
//�~�j�K���̃X�g���e�W�[�p�^�[��[minigun_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "minigun_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CMiniGunShot::CMiniGunShot()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMiniGunShot::~CMiniGunShot()
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CMiniGunReload::CMiniGunReload()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMiniGunReload::~CMiniGunReload()
{
}

//=============================================
//�����[�h
//=============================================
bool CMiniGunReload::Reload(CGun* gun)
{
	bool bReload = true; //�����[�h�����ǂ���
	int nCnt = GetReloadCnt();

	++nCnt;

	if (nCnt >= CMiniGun::DEFAULT_MINIGUN_RELOAD_FRAME)
	{
		nCnt = 0;
		//���݂̒e���擾
		int nAmmo = gun->GetAmmo();
		//�f�t�H���g�̃}�K�W���e�����
		nAmmo = CMiniGun::DEFAULT_MINIGUN_MAG_SIZE;
		gun->SetAmmo(nAmmo);
		bReload = false;
	}

	SetReloadCnt(nCnt);
	return bReload;
}
