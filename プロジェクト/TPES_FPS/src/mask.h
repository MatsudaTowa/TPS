//=============================================
//
//�}�X�N����[mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MASK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MASK_H_
#include "main.h"
#include "scene.h"
#include "object2D.h"

//=============================================
//�}�X�N�N���X
//=============================================
class CMask : public CObject2D
{
public:
	static const int MASK_PRIORITY = 12;  //�`�揇
	static const int REFARENCE_VALUE = 2;  //�`��Q�ƒl

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMask()override;
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
	 * @return �}�X�N�|�C���^
	 */
	static CMask* Create();
private:
};
#endif