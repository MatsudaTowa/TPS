//=============================================
//
//�Z���^�[�h�b�g[centerdot.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CENTERDOT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CENTERDOT_H_

//=============================================
//�Z���^�[�h�b�g�N���X
//=============================================
class CCenterDot : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 19; //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CCenterDot(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CCenterDot()override;
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
	 * @return �Z���^�[�h�b�g�̃|�C���^
	 */
	static CCenterDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CENTERDOT_TEXTURE_NAME;	//�e�N�X�`���̖��O
};

#endif