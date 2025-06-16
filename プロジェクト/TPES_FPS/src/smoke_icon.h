//=============================================
//
//�X���[�N�̕\�L[smoke_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SMOKE_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�X���[�N�̕\�L�N���X
//=============================================
class CSmokeIcon : public CObject2D
{
public:
	static const int SMOKE_ICON_PRIORITY = 21;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSmokeIcon(int nPriority = SMOKE_ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSmokeIcon()override;
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
	 * @return 
	 */
	static CSmokeIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif