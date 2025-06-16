//=============================================
//
//�e[gun.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "bullet.h"
#include "gun_behavior.h"

#ifndef _GUN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GUN_H_

//=============================================
//�O���錾
//=============================================
class CShot;
class CReload;

//=============================================
//�e�̊��N���X
//=============================================
class CGun
{
public:
	static const int DEFAULT_HG_MAG_SIZE = 20; //�f�t�H���g�̃n���h�K���̃}�K�W���T�C�Y
	static const int DEFAULT_SG_MAG_SIZE = 6; //�f�t�H���g�̃V���b�g�K���̃}�K�W���T�C�Y

	static const int DEFAULT_HG_RELOAD_FRAME = 20; //�f�t�H���g�̃n���h�K���̃����[�h�t���[����
	static const int DEFAULT_SG_RELOAD_FRAME = 30; //�f�t�H���g�̃n���h�K���̃����[�h�t���[����

	/**
	 * @brief �R���X�g���N�^
	 */
	CGun();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CGun();
	/**
	 * @brief ������
	 * @return ����������
	 */
	virtual HRESULT Init() = 0;
	/**
	 * @brief �I��
	 */
	virtual void Uninit() = 0;
	/**
	 * @brief �����[�h
	 * @return �����[�h���I�������
	 */
	virtual bool Reload();
	/**
	 * @brief �T�C�Y�ݒ�
	 * @param [in]�T�C�Y
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_Size = size;
	}

	/**
	 * @brief ���[�g�v���J�E���g�ݒ�
	 * @param [in]���[�g�J�E���g
	 */
	inline void SetRateCnt(int nRateCnt)
	{
		m_nRateCnt = nRateCnt;
	}

	/**
	 * @brief �e���ݒ�
	 * @param [in]�e��
	 */	inline void SetAmmo(int Ammo)
	{
		m_Ammo = Ammo;
	}

	/**
	 * @brief �_���[�W�ݒ�
	 * @param [in]�_���[�W
	 */
	inline void SetDamage(int Damage)
	{
		m_nDamage = Damage;
	}

	/**
	 * @brief �����[�h�t���[���ݒ�
	 * @param [in]�����[�h�t���[��
	 */
	inline void SetReloadFrame(int ReloadFrame)
	{
		m_ReloadFrame = ReloadFrame;
	}
	/**
	 * @brief ���˃��[�g�ݒ�
	 * @param [in]���˃��[�g
	 */
	inline void SetFireRate(int FireRate)
	{
		m_FireRate = FireRate;
	}

	/**
	 * @brief �e���ݒ�
	 * @param [in]�e��
	 */
	inline void SetBulletSpeed(float BulletSpeed)
	{
		m_BulletSpeed = BulletSpeed;
	}
	
	/**
	 * @brief �T�C�Y�擾
	 * @return �T�C�Y
	 */
	inline D3DXVECTOR3& GetSize()
	{
		return m_Size;
	}

	/**
	 * @brief ���[�g�J�E���g�擾
	 * @return ���[�g�J�E���g
	 */
	inline int& GetRateCnt()
	{
		return m_nRateCnt;
	}

	/**
	 * @brief �e���擾
	 * @return �e��
	 */
	inline int& GetAmmo()
	{
		return m_Ammo;
	}

	/**
	 * @brief �_���[�W�擾
	 * @return �_���[�W
	 */
	inline int& GetDamage()
	{
		return m_nDamage;
	}

	/**
	 * @brief �����[�h�t���[���擾
	 * @return �����[�h�t���[��
	 */
	inline int& GetReloadFrame()
	{
		return m_ReloadFrame;
	}

	/**
	 * @brief ���˃��[�g�擾
	 * @return ���˃��[�g
	 */
	inline int& GetFireRate()
	{
		return m_FireRate;
	}

	/**
	 * @brief �e���擾
	 * @return �e��
	 */
	inline float& GetBulletSpeed()
	{
		return m_BulletSpeed;
	}

	CShot* m_pShot; //�e���ˏ���
	CReload* m_pReload; //�����[�h����

private:
	D3DXVECTOR3 m_Size; //�T�C�Y

	int m_nRateCnt;//���[�g�J�E���g
	int m_Ammo; //�}�K�W�����̒e��
	int m_nDamage; //�_���[�W
	int m_ReloadFrame; //�����[�h�t���[��
	int m_FireRate; //���˃��[�g
	float m_BulletSpeed; //�e��

};

//=============================================
//�A�T���g���C�t�N���X
//=============================================
class CAssultRifle :public CGun
{
public:
	static const int DEFAULT_AR_MAG_SIZE = 28; //�f�t�H���g�̃A�T���g�̃}�K�W���T�C�Y
	static const int DEFAULT_AR_FIRE_RATE = 13; //�f�t�H���g�̃A�T���g�̔��˃��[�g
	static constexpr float DEFAULT_AR_BULLET_SPEED = 100.0f; //�f�t�H���g�̃A�T���g�̒e�̃X�s�[�h
	static const D3DXVECTOR3 DEFAULT_AR_SIZE; //�f�t�H���g�̃A�T���g�T�C�Y
	static const int DEFAULT_AR_RELOAD_FRAME = 120; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int DEFAULT_AR_DAMAGE = 10; //�f�t�H���g�̃A�T���g�̃_���[�W

	/**
	 * @brief �R���X�g���N�^
	 */
	CAssultRifle();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAssultRifle() override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
private:
};

//=============================================
//�~�j�K���N���X
//=============================================
class CMiniGun :public CGun
{
public:
	static const int DEFAULT_MINIGUN_MAG_SIZE = 120; //�f�t�H���g�̃~�j�K���̃}�K�W���T�C�Y
	static const int DEFAULT_MINIGUN_RELOAD_FRAME = 120; //�f�t�H���g�̃~�j�K���̃����[�h�t���[����
	static const int DEFAULT_MINIGUN_FIRE_RATE = 2; //�f�t�H���g�̃~�j�K���̔��˃��[�g
	static const int DEFAULT_MINIGUN_DAMAGE = 3; //�f�t�H���g�̃~�j�K���̃_���[�W
	static constexpr float DEFAULT_MINIGUN_BULLET_SPEED = 100.0f; //�f�t�H���g�̃~�j�K���̒e�̃X�s�[�h
	static const D3DXVECTOR3 DEFAULT_MINIGUN_SIZE; //�f�t�H���g�̃~�j�K���̃T�C�Y

	/**
	 * @brief �R���X�g���N�^
	 */
	CMiniGun();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMiniGun() override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
private:
};
#endif