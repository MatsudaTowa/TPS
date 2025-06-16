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
	/**
	 * @brief �R���X�g���N�^
	 */
	CAssaultShot();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAssaultShot() override;
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CAssaultReload : public CReload
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CAssaultReload();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAssaultReload() override;
	/**
	 * @brief �����[�h����
	 * @param [in]�e�̃|�C���^
	 * @return ���Ă邩�ǂ���
	 */
	bool Reload(CGun* gun) override;
private:
};
#endif