//=============================================
//
//�e[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
#include "minigun_behavior.h"
//=============================================
//�R���X�g���N�^
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate(), m_nRateCnt(0),m_nDamage(0),m_Size(),m_BulletSpeed(0.0f)
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
		m_pShot = nullptr;
	}
	if (m_pReload != nullptr)
	{
		delete m_pReload;
		m_pReload = nullptr;
	}
}

//=============================================
//�����[�h
//=============================================
bool CGun::Reload()
{
	bool bReload = true; //�����[�h�����ǂ���
	if (m_pReload != nullptr)
	{
		bReload = m_pReload->Reload(this);
	}
	return bReload;
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
//�e���擾
//=============================================
float& CGun::GetBulletSpeed()
{
	return m_BulletSpeed;
}

//�e�̃X�s�[�h
const float CAssultRifle::DEFAULT_AR_BULLET_SPEED = 50.0f;
//�e�̃T�C�Y
const D3DXVECTOR3 CAssultRifle::DEFAULT_AR_SIZE = {1.5f,1.5f,1.5f};

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
	//���݂̒e���擾
	float fBulletSpeed = GetBulletSpeed();

	//�f�t�H���g�̃}�K�W���e�����
	nAmmo = DEFAULT_AR_MAG_SIZE;
	//�������x�����
	nLv = 1;
	//�f�t�H���g�̃����[�h�t���[�����
	nReloadFrame = DEFAULT_AR_RELOAD_FRAME;
	//�f�t�H���g�̔��˃��[�g���
	nFireRate = DEFAULT_AR_FIRE_RATE;
	//�f�t�H���g�̒e�����
	fBulletSpeed = DEFAULT_AR_BULLET_SPEED;

	//�������炷�����˂��邽��
	m_nRateCnt = DEFAULT_AR_FIRE_RATE;

	//�_���[�W�̑��
	m_nDamage = DEFAULT_AR_DAMAGE;

	//�T�C�Y�̑��
	m_Size = DEFAULT_AR_SIZE;

	//�e�����o�[�ϐ��ɑ��
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);
	SetBulletSpeed(fBulletSpeed);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAssultRifle::Uninit()
{
}

//�e�̃X�s�[�h
const float CMiniGun::DEFAULT_MINIGUN_BULLET_SPEED = 50.0f;
//�e�̃T�C�Y
const D3DXVECTOR3 CMiniGun::DEFAULT_MINIGUN_SIZE = { 1.0f,1.0f,1.0f };
//=============================================
//�R���X�g���N�^
//=============================================
CMiniGun::CMiniGun()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CMiniGunShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CMiniGunReload;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CMiniGun::~CMiniGun()
{
}

//=============================================
//������
//=============================================
HRESULT CMiniGun::Init()
{
	//���݂̒e���擾
	int nAmmo = GetAmmo();
	//���݂̃��x���擾
	int nLv = GetLv();
	//���݂̃����[�h�t���[���擾
	int nReloadFrame = GetReloadFrame();
	//���݂̔��˃��[�g�擾
	int nFireRate = GetFireRate();
	//���݂̒e���擾
	float fBulletSpeed = GetBulletSpeed();

	//�f�t�H���g�̃}�K�W���e�����
	nAmmo = DEFAULT_MINIGUN_MAG_SIZE;
	//�������x�����
	nLv = 1;
	//�f�t�H���g�̃����[�h�t���[�����
	nReloadFrame = DEFAULT_MINIGUN_RELOAD_FRAME;
	//�f�t�H���g�̔��˃��[�g���
	nFireRate = DEFAULT_MINIGUN_FIRE_RATE;
	//�f�t�H���g�̒e�����
	fBulletSpeed = DEFAULT_MINIGUN_BULLET_SPEED;

	//�������炷�����˂��邽��
	m_nRateCnt = DEFAULT_MINIGUN_FIRE_RATE;

	//�_���[�W�̑��
	m_nDamage = DEFAULT_MINIGUN_DAMAGE;

	//�T�C�Y�̑��
	m_Size = DEFAULT_MINIGUN_SIZE;

	//�e�����o�[�ϐ��ɑ��
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);
	SetBulletSpeed(fBulletSpeed);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMiniGun::Uninit()
{
}
