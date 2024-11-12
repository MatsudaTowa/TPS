//=============================================
//
//�e[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
//=============================================
//�R���X�g���N�^
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate(), m_nRateCnt(0)
{
	m_pShot = nullptr;
	m_pReload = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CGun::~CGun()
{
	if (m_pShot != nullptr)
	{
		delete m_pShot;
	}
	if (m_pReload != nullptr)
	{
		delete m_pReload;
	}
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

//�e�̃X�s�[�h
const float CAssultRifle::DEFAULT_AR_BULLET_SPEED = 15.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CAssultRifle::CAssultRifle()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CAssaultShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CAssaultReload;
	}
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
	if (m_pShot != nullptr)
	{
		m_pShot->Shot(pos, move, size, nDamage, Allegiance, type, this);
	}
}

//=============================================
//�����[�h����
//=============================================
bool CAssultRifle::Reload()
{
	bool bReload = true; //�����[�h�����ǂ���
	if (m_pReload != nullptr)
	{
		bReload = m_pReload->Reload(this);
	}
	return bReload;
}
