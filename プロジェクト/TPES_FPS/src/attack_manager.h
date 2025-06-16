//=============================================
//
//�U���Ǘ��N���X[attack_manager.h]
//Author Matsuda Towa
//
//=============================================
#include"main.h"
#include "Billboard.h"

#ifndef _ATTACK_MANAGER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ATTACK_MANAGER_H_

//=============================================
//�U���Ǘ��N���X
//=============================================
class CAttack_Manager : public CBillboard
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CAttack_Manager(int nPriority);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAttack_Manager()override;
	/**
	 * @brief ������
	 * @return �������Ă邩
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
	/**
	 * @brief �G�Ƃ̃q�b�g����
	 * @return �q�b�g���Ă邩
	 */
	bool HitEnemy();
	/**
	 * @brief �v���C���[�Ƃ̃q�b�g����
	 * @return �q�b�g���Ă邩
	 */
	bool HitPlayer();
	/**
	 * @brief �u���b�N�Ƃ̃q�b�g����
	 * @return �q�b�g���Ă邩
	 */
	bool HitBlock();
	/**
	 * @brief ���Ƃ̃q�b�g����
	 * @return �q�b�g���Ă邩
	 */
	bool HitGround();

	/**
	 * @brief �̗͂̐ݒ�
	 * @param [in]�̗�
	 */
	inline void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	/**
	 * @brief �_���[�W�̐ݒ�
	 * @param [in]�_���[�W�̒l
	 */
	inline void SetDamage(int nDamage)
	{
		m_nDamage = nDamage;
	}

	/**
	 * @brief �̗͂̎擾
	 * @return �̗͂̒l
	 */
	inline int GetLife()
	{
		return m_nLife;
	}

	/**
	 * @brief �_���[�W�̎擾
	 * @return �_���[�W�̒l
	 */
	inline int GetDamage()
	{
		return m_nDamage;
	}
private:
	int m_nLife; //����
	int m_nDamage; //�_���[�W
	int m_nNumkill; //���̓|������
};
#endif