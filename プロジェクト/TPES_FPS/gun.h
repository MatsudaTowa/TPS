//=============================================
//
//�e[gun.h]
//Auther Matsuda Towa
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

	CGun();
	virtual ~CGun();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
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

	int m_nRateCnt;//���[�g�J�E���g

	CShot* m_pShot; //�e���ˏ���
	CReload* m_pReload; //�����[�h����

	int m_nDamage; //�_���[�W
	D3DXVECTOR3 m_Size; //�T�C�Y
private:
	int m_Ammo; //�}�K�W�����̒e��
	int m_Lv; //�e�̃��x��
	int m_ReloadFrame; //�����[�h�t���[��
	int m_FireRate; //���˃��[�g

};

//=============================================
//�A�T���g���C�t�N���X
//=============================================
class CAssultRifle :public CGun
{
public:
	static const int DEFAULT_AR_MAG_SIZE = 28; //�f�t�H���g�̃A�T���g�̃}�K�W���T�C�Y
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int DEFAULT_AR_FIRE_RATE = 25; //�f�t�H���g�̃A�T���g�̔��˃��[�g
	static const int DEFAULT_AR_DAMAGE = 1; //�f�t�H���g�̃A�T���g�̃_���[�W
	static const float DEFAULT_AR_BULLET_SPEED; //�f�t�H���g�̃A�T���g�̒e�̃X�s�[�h
	static const D3DXVECTOR3 DEFAULT_AR_SIZE; //�f�t�H���g�̃A�T���g�T�C�Y

	CAssultRifle();
	~CAssultRifle() override;
	HRESULT Init() override;
	void Uninit() override;
	bool Reload() override;
private:
};
#endif