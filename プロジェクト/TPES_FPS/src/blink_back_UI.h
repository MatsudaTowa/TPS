//=============================================
//
//�u�����N�̐����̔w�i[blink_back_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLINK_BACK_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BLINK_BACK_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�u�����NUI�̔w�i�N���X
//=============================================
class CBlinkBackUI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBlinkBackUI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBlinkBackUI()override;
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
	 * @return �u�����N��UI�̔w�i
	 */
	static CBlinkBackUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif