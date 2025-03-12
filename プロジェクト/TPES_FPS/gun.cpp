//=============================================
//
//�e[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
#include "minigun_behavior.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CGun::CGun():
m_Ammo(),					//�e��
m_ReloadFrame(),			//�����[�h�̃t���[��
m_FireRate(),				//���˃��[�g
m_nRateCnt(INT_ZERO),		//���[�g�v��
m_nDamage(INT_ZERO),		//�_���[�W
m_Size(),					//�e�̃T�C�Y
m_pShot(),					//���ˏ���
m_pReload(),				//�����[�h����
m_BulletSpeed(FLOAT_ZERO)	//�e�̃X�s�[�h
{
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

//�e�̃T�C�Y
const D3DXVECTOR3 CAssultRifle::DEFAULT_AR_SIZE = {2.0f,2.0f,2.0f};

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
	//���݂̃����[�h�t���[���擾
	int nReloadFrame = GetReloadFrame();
	//���݂̔��˃��[�g�擾
	int nFireRate = GetFireRate();
	//���݂̒e���擾
	float fBulletSpeed = GetBulletSpeed();

	//�f�t�H���g�̃}�K�W���e�����
	nAmmo = DEFAULT_AR_MAG_SIZE;

	//�f�t�H���g�̔��˃��[�g���
	nFireRate = DEFAULT_AR_FIRE_RATE;
	//�f�t�H���g�̒e�����
	fBulletSpeed = DEFAULT_AR_BULLET_SPEED;

	//�������炷�����˂��邽��
	m_nRateCnt = GetFireRate();

	//�T�C�Y�̑��
	m_Size = DEFAULT_AR_SIZE;

	//�e�����o�[�ϐ��ɑ��
	SetAmmo(nAmmo);
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
	//���݂̃����[�h�t���[���擾
	int nReloadFrame = GetReloadFrame();
	//���݂̔��˃��[�g�擾
	int nFireRate = GetFireRate();
	//���݂̒e���擾
	float fBulletSpeed = GetBulletSpeed();

	//�f�t�H���g�̃}�K�W���e�����
	nAmmo = DEFAULT_MINIGUN_MAG_SIZE;

	//�f�t�H���g�̃����[�h�t���[�����
	nReloadFrame = DEFAULT_MINIGUN_RELOAD_FRAME;
	//�f�t�H���g�̔��˃��[�g���
	nFireRate = DEFAULT_MINIGUN_FIRE_RATE;
	//�f�t�H���g�̒e�����
	fBulletSpeed = DEFAULT_MINIGUN_BULLET_SPEED;

	//�������炷�����˂��邽��
	m_nRateCnt = DEFAULT_MINIGUN_FIRE_RATE;

	//�_���[�W�̑��
	SetDamage(DEFAULT_MINIGUN_DAMAGE);

	//�T�C�Y�̑��
	m_Size = DEFAULT_MINIGUN_SIZE;

	//�e�����o�[�ϐ��ɑ��
	SetAmmo(nAmmo);
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
