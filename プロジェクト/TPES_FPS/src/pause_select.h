//=============================================
//
//�u�����N�̕\�L[blink_icon.h]
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
	static const int PRIORITY = 21;  //�`�揇

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
	 * @return �|�[�Y��UI�|�C���^
	 */
	static CPauseSelect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif