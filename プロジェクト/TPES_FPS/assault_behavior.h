//=============================================
//
//�A�T���g�e�̃X�g���e�W�[�p�^�[��[assault_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ASSAULT_BEHAVIOR_
#define _ASSAULT_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//�A�T���g�e���˃X�g���e�W�[
//=============================================
class CAssaultShot : public CShot
{
public:
	CAssaultShot();
	~CAssaultShot() override;
	void Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun* gun) override;
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CAssaultReload : public CReload
{
public:
	CAssaultReload();
	~CAssaultReload() override;
	bool Reload(CGun* gun) override;
private:
};
#endif