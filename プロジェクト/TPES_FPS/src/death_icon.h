//=============================================
//
//���S�A�C�R��[death_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DEATH_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _DEATH_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//���S�A�C�R���N���X
//=============================================
class CDeathIcon : public CObject2D
{
public:
	static const int PRIORITY = 27;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CDeathIcon(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CDeathIcon()override;
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
	 * @return ���S�A�C�R���̃|�C���^
	 */
	static CDeathIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif
