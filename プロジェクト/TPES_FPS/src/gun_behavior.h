//=============================================
//
//�e�̃X�g���e�W�[�p�^�[��[gun_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GUN_BEHAVIOR_
#define _GUN_BEHAVIOR_
#include "gun.h"
#include "muzzle_flash.h"

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
	/**
	 * @brief �R���X�g���N�^
	 */
	CShot();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CShot();
	/**
	 * @brief ����
	 * @param [in]�ʒu
	 * @param [in]�ړ���
	 * @param [in]�T�C�Y
	 * @param [in]�_���[�W
	 * @param [in]�ǂ����̒e��
	 * @param [in]�e�̃|�C���^
	 */
	virtual void Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance,CGun*gun);
private:
	static const int LIFE = 900;	//���� 
};

//=============================================
//�����[�h�X�g���e�W�[
//=============================================
class CReload
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CReload();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CReload();
	/**
	 * @brief �����[�h
	 * @param [in]�e�̃|�C���^
	 * @return �����[�h���I�������
	 */
	virtual bool Reload(CGun* gun) = 0;

	/**
	 * @brief �����[�h�J�E���g�擾
	 * @return �����[�h�J�E���g
	 */
	inline int& GetReloadCnt() 
	{
		return m_nReloadCnt;
	}

	/**
	 * @brief �����[�h�J�E���g�ݒ�
	 * @param [in]�����[�h�J�E���g
	 */
	inline void SetReloadCnt(int nCnt)
	{
		m_nReloadCnt = nCnt;
	}
private:
	int m_nReloadCnt;
};

#endif
