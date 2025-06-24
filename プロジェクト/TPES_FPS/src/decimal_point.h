//=============================================
//
//�����_[decimal_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DECIMAL_POINT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _DECIMAL_POINT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�����_�N���X
//=============================================
class CDecimalPoint : public CObject2D
{
public:
	static const int PRIORITY = 29;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CDecimalPoint(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CDecimalPoint()override;
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
	 * @param [in]�T�C�Y
	 * @param [in]�F
	 * @return �����_�|�C���^
	 */
	static CDecimalPoint* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,D3DXCOLOR col);
private:
};
#endif