//=============================================
//
//�e�̃X�g���e�W�[�p�^�[��[gun_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GUN_BEHAVIOR_
#define _GUN_BEHAVIOR_
#include "gun.h"

//=============================================
//�O���錾
//=============================================
class CGun;

//=============================================
//�e���˃X�g���e�W�[
//=============================================
class CShot
{
public:
	CShot();
	virtual ~CShot();
	virtual void Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun*gun) = 0;
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CReload
{
public:
	CReload();
	virtual ~CReload();
	virtual bool Reload(CGun* gun) = 0;

	int& GetReloadCnt();

	void SetReloadCnt(int nCnt)
	{
		m_nReloadCnt = nCnt;
	}
private:
	int m_nReloadCnt;
};

#endif
