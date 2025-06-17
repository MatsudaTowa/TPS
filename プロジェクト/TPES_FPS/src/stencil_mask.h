//=============================================
//
//�X�e���V���}�X�N����[stencil_mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _STENCIL_MASK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _STENCIL_MASK_H_
#include "main.h"
#include "mask.h"

//=============================================
//�X�e���V���}�X�N�N���X
//=============================================
class CStencilMask : public CMask
{
public:
	static const int REFARENCE_VALUE = 2;  //�`��Q�ƒl

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CStencilMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CStencilMask()override;
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
private:
	static const D3DXCOLOR COLOR;
};
#endif