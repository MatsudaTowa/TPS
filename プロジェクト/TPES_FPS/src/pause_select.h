//=============================================
//
//�|�[�Y��UI[pause_select.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PAUSE_SELECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�|�[�Y�I��UI�N���X
//=============================================
class CPauseSelect : public CObject2D
{
public:
	static const int PRIORITY = 29;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CPauseSelect(int nPriority = PRIORITY);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CPauseSelect()override;
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
	 * @param [in]�|�[�Y��UI�|�C���^
	 * @return �|�[�Y��UI�|�C���^
	 */
	static CPauseSelect* Create(D3DXVECTOR3 pos,CPauseSelect* select);

	/**
	 * @brief �I�����ꂽ��
	 * @return �ǂ��I�����ꂽ��
	 */
	bool GetSelect()
	{
		return m_isSelect;
	}

	/**
	 * @brief �I�����ꂽ��
	 * @param [in]isSelect
	 */
	void SetSelect(bool isSelect)
	{
		m_isSelect = isSelect;
	}

private:
	static const D3DXCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 SIZE;
	bool m_isSelect;	//�}�E�X�J�[�\���ƃq�b�g������
};
#endif