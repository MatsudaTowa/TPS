//=============================================
//
//�A�T���g�e�̃X�g���e�W�[�p�^�[��[assault_behavior.h]
//Author Matsuda Towa
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