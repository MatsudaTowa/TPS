//=============================================
//
//�r���{�[�h[billboard.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BILLBOARD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

//=============================================
//�r���{�[�h�N���X
//=============================================
class CBillboard : public CObject3D
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBillboard(int nPriority);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBillboard()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
};
#endif