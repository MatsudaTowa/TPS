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

	if (nCnt >= gun->GetReloadFrame())
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
