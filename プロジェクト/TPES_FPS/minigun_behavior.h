//=============================================
//
//�~�j�K���̃X�g���e�W�[�p�^�[��[minigun_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MINIGUN_BEHAVIOR_
#define _MINIGUN_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//�~�j�K���̒e���˃X�g���e�W�[
//=============================================
class CMiniGunShot : public CShot
{
public:
	CMiniGunShot();
	~CMiniGunShot() override;
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CMiniGunReload : public CReload
{
public:
	CMiniGunReload();
	~CMiniGunReload() override;
	bool Reload(CGun* gun) override;
private:
};
#endif