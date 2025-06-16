//=============================================
//
//�u�����N�̕\�L[blink_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLINK_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BLINK_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�u�����N��UI�N���X
//=============================================
class CBlinkIcon : public CObject2D
{
public:
	static const int ICON_PRIORITY = 21;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBlinkIcon(int nPriority = ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBlinkIcon()override;
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
	 * @return �u�����N��UI�̃A�C�R���|�C���^
	 */
	static CBlinkIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif