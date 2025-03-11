//=============================================
//
//�e�̃X�g���e�W�[�p�^�[��[gun_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun_behavior.h"
#include "manager.h"

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
	if (nAmmo > INT_ZERO)
	{//�}�K�W�����ɒe�������
		//�e�𐶐�
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			VEC3_RESET_ZERO, D3DXVECTOR3(size.x, size.y, FLOAT_ZERO), LIFE, nDamage, Allegiance, type);

		//�}�Y���t���b�V���𐶐�
		CMuzzleFlash::Create(pos);

		//�e�������炷
		--nAmmo;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//�R���X�g���N�^
//=============================================
CReload::CReload():m_nReloadCnt(INT_ZERO)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CReload::~CReload()
{
}
