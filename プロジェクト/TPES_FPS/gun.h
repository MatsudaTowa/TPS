//=============================================
//
//�e[gun.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "bullet.h"

#ifndef _GUN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GUN_H_

class CGun
{
public:
	static const int DEFAULT_HG_MAG_SIZE = 20; //�f�t�H���g�̃n���h�K���̃}�K�W���T�C�Y
	static const int DEFAULT_SG_MAG_SIZE = 6; //�f�t�H���g�̃V���b�g�K���̃}�K�W���T�C�Y

	static const int DEFAULT_HG_RELOAD_FRAME = 20; //�f�t�H���g�̃n���h�K���̃����[�h�t���[����
	static const int DEFAULT_SG_RELOAD_FRAME = 30; //�f�t�H���g�̃n���h�K���̃����[�h�t���[����

	CGun();
	virtual ~CGun();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type) = 0; //�e���ˏ���
	virtual bool Reload() = 0;

	//�e���ݒ�
	void SetAmmo(int Ammo)
	{
		m_Ammo = Ammo;
	}
	//���x���ݒ�
	void SetLv(int Lv)
	{
		m_Lv = Lv;
	}
	//�����[�h�t���[���ݒ�
	void SetReloadFrame(int ReloadFrame)
	{
		m_ReloadFrame = ReloadFrame;
	}
	//���˃��[�g�ݒ�
	void SetFireRate(int FireRate)
	{
		m_FireRate = FireRate;
	}
	
	//�e���擾
	int& GetAmmo();
	//���x���擾
	int& GetLv();
	//�����[�h�t���[��
	int& GetReloadFrame();
	//���˃��[�g�擾
	int& GetFireRate();
private:
	int m_Ammo; //�}�K�W�����̒e��
	int m_Lv; //�e�̃��x��
	int m_ReloadFrame; //�����[�h�t���[��
	int m_FireRate; //���˃��[�g
};

class CAssultRifle :public CGun
{
public:
	static const int DEFAULT_AR_MAG_SIZE = 28; //�f�t�H���g�̃A�T���g�̃}�K�W���T�C�Y
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int DEFAULT_AR_FIRE_RATE = 15; //�f�t�H���g�̃A�T���g�̔��˃��[�g
	static const float DEFAULT_AR_BULLET_SPEED; //�f�t�H���g�̃A�T���g�̒e�̃X�s�[�h

	CAssultRifle();
	~CAssultRifle() override;
	HRESULT Init() override;
	void Uninit() override;
	void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type) override; //�e���ˏ���
	bool Reload() override;
private:
	int m_nReloadCnt;
};
#endif