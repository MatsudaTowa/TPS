//=============================================
//
//�����[�h�̕\�L[reload_txt.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _RELOAD_TXT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _RELOAD_TXT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�����[�h�̕\�L�N���X
//=============================================
class CReloatTxt : public CObject2D
{
public:
	static const int PRIORITY = 21;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CReloatTxt(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CReloatTxt()override;
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
	static CReloatTxt* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif