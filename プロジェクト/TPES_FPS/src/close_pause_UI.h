//=============================================
//
//�|�[�Y���Ƃ���UI[close_pause_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CLOSE_PAUSE_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CLOSE_PAUSE_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�|�[�Y���Ƃ���UI�N���X
//=============================================
class CClosePauseUI : public CObject2D
{
public:
	static const int PRIORITY = 29;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CClosePauseUI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CClosePauseUI()override;
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
	 * @return �|�[�Y�����UI�|�C���^
	 */
	static CClosePauseUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif