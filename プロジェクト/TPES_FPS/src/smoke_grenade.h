//=============================================
//
//�X���[�N�O���l�[�h����[somoke_grenade.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_GRENADE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_GRENADE_H_

//=============================================
// �X���[�N�O���l�[�h�N���X
//=============================================
class CSmokeGrenade : public CObjectX
{
public:
	static const int SMOKE_PRIORITY = 24; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSmokeGrenade(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSmokeGrenade()override;
	/**
	 * @brief ������
	 * @return ����������
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
	 * @brief ����
	 * @param [in]�ʒu
	 * @param [in]�ړ���
	 * @param [in]����
	 * @return �X���[�N�O���l�[�h�̃|�C���^
	 */
	static CSmokeGrenade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//���f���̖��O
	static const int CREATE_SMOKE_NUM = 100; //��������X���[�N�̐�
	/**
	 * @brief �n�ʂƐڐG������
	 */
	void HitField();
	D3DXVECTOR3 m_oldpos;
	D3DXVECTOR3 m_move;
	bool m_bBoot; //�O���l�[�h���N��������
	int m_NumCreate; //�������������J�E���g����ϐ�
};

#endif