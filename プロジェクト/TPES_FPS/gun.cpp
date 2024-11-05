//=============================================
//
//�e[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"

//=============================================
//�R���X�g���N�^
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGun::~CGun()
{
}

//=============================================
//�e���擾
//=============================================
int& CGun::GetAmmo()
{
	return m_Ammo;
}

//=============================================
//���x���擾
//=============================================
int& CGun::GetLv()
{
	return m_Lv;
}

//=============================================
//�����[�h�t���[���擾
//=============================================
int& CGun::GetReloadFrame()
{
	return m_ReloadFrame;
}

//=============================================
//���˃��[�g�擾
//=============================================
int& CGun::GetFireRate()
{
	return m_FireRate;
}

//=============================================
//�R���X�g���N�^
//=============================================
CAssultRifle::CAssultRifle(): m_nReloadCnt()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CAssultRifle::~CAssultRifle()
{
}

//=============================================
//������
//=============================================
HRESULT CAssultRifle::Init()
{
	//���݂̒e���擾
	int nAmmo = GetAmmo();
	//���݂̃��x���擾
	int nLv = GetLv();
	//���݂̃����[�h�t���[���擾
	int nReloadFrame = GetReloadFrame();
	//���݂̔��˃��[�g�擾
	int nFireRate = GetFireRate();

	//�f�t�H���g�̃}�K�W���e�����
	nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
	//�������x�����
	nLv = 1;
	//�f�t�H���g�̃����[�h�t���[�����
	nReloadFrame = CAssultRifle::DEFAULT_AR_RELOAD_FRAME;
	//�f�t�H���g�̔��˃��[�g���
	nFireRate = CAssultRifle::DEFAULT_AR_FIRE_RATE;

	//�e�����o�[�ϐ��ɑ��
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);

	m_nReloadCnt = 0;

	return S_OK;
}

//=============================================
//�X�V
//=============================================
void CAssultRifle::Uninit()
{
}

//=============================================
//�e���ˏ���
//=============================================
void CAssultRifle::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type)
{
	//���݂̒e���擾
	int nAmmo = GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 300, nDamage, Allegiance, type);
		nAmmo--;
	}
	SetAmmo(nAmmo);
}

//=============================================
//�����[�h����
//=============================================
bool CAssultRifle::Reload()
{
	bool bReload = true; //�����[�h�����ǂ���
	m_nReloadCnt++;
	if (m_nReloadCnt >= CAssultRifle::DEFAULT_AR_RELOAD_FRAME)
	{
		m_nReloadCnt = 0;
		//���݂̒e���擾
		int nAmmo = GetAmmo();
		//�f�t�H���g�̃}�K�W���e�����
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		SetAmmo(nAmmo);
		bReload = false;
	}
	return bReload;
}
