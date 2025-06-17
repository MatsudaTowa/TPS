//=============================================
//
//�N���X�w�A[crosshair.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CROSSHAIR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CROSSHAIR_H_

//=============================================
//�N���X�w�A�N���X
//=============================================
class CCrossHair : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 18; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CCrossHair(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CCrossHair()override;
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
	 * @param [in]�T�C�Y
	 * @param [in]�F
	 * @return �N���X�w�A�|�C���^
	 */
	static CCrossHair* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CROSSHAIR_TEXTURE_NAME;	//�e�N�X�`���̖��O

	D3DXVECTOR3 m_move; //�ړ���
};

#endif