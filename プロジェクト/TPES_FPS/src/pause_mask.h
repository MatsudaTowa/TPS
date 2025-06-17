//=============================================
//
//�|�[�Y�}�X�N����[pausel_mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_MASK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PAUSE_MASK_H_
#include "main.h"
#include "mask.h"

//=============================================
//�|�[�Y�}�X�N�N���X
//=============================================
class CPauseMask : public CMask
{
public:
	static const int MASK_PRIORITY = 28;
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CPauseMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPauseMask()override;
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