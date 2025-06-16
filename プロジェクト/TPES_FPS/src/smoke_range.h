//=============================================
//
//�X���[�N�͈͏���[somoke_range.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_RANGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_RANGE_H_

//=============================================
// �X���[�N�͈̔̓N���X
//=============================================
class CSmokeRange : public CObjectX
{
public:
	static const int SMOKE_RANGE_PRIORITY = 15; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSmokeRange(int nPriority = SMOKE_RANGE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSmokeRange()override;
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
	 * @param [in]����
	 * @return �X���[�N�͈̔͂̃|�C���^
	 */
	static CSmokeRange* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//���f���̖��O
	int m_nLife;
};

#endif