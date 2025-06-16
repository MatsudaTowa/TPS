//=============================================
//
//���U���g���[result_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _RESULT_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RESULT_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
//���U���g��ʃN���X
//=============================================
class CResult_Screen : public CObject2D
{
public:
	static const int RESULT_SCREEN_PRIORITY = 20;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CResult_Screen(int nPriority = RESULT_SCREEN_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CResult_Screen()override;
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
	 * @return ���U���g�̉�ʃ|�C���^
	 */
	static CResult_Screen* Create(D3DXVECTOR3 pos);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif