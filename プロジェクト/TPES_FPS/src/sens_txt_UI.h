//=============================================
//
//���x�̕���UI[sens_txt_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SENS_TXT_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SENS_TXT_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//���x�̕���UI�N���X
//=============================================
class CSensTxtUI : public CObject2D
{
public:
	static const int PRIORITY = 29;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSensTxtUI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSensTxtUI()override;
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
	 * @return ���x�̕���UI�|�C���^
	 */
	static CSensTxtUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif