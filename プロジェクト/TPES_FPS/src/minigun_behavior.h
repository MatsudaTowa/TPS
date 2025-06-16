//=============================================
//
//�~�j�K���̃X�g���e�W�[�p�^�[��[minigun_behavior.h]
//Author Matsuda Towa
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
	/**
	 * @brief �R���X�g���N�^
	 */
	CMiniGunShot();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMiniGunShot() override;
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CMiniGunReload : public CReload
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CMiniGunReload();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMiniGunReload() override;
	/**
	 * @brief �����[�h
	 * @param [in]�e�̃|�C���^
	 * @return �����[�h���I�������
	 */
	bool Reload(CGun* gun) override;
private:
};
#endif