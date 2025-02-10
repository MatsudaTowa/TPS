//=============================================
//
//�U���Ǘ��N���X[attack_manager.h]
//Auther Matsuda Towa
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
	CAttack_Manager(int nPriority);
	~CAttack_Manager()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	bool HitEnemy();
	bool HitPlayer();
	bool HitBlock();
	bool HitGround();

	//�����̐ݒ�
	inline void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//�_���[�W�̐ݒ�
	inline void SetDamage(int nDamage)
	{
		m_nDamage = nDamage;
	}

	//�����̎擾
	inline int GetLife()
	{
		return m_nLife;
	}

	//�_���[�W�̎擾
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