//=============================================
//
//�`���[�g���A���X�N���[��[tutorial_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TUTORIAL_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
// �`���[�g���A����ʃN���X
//=============================================
class CTutorial_Screen : public CObject2D
{
public:
	enum TUTORIAL_UI
	{
		UI_NONE = 0,
		UI_TUTORIAL_TXT,
		UI_TITLE_PRESS_BUTTON,
		UI_TITLE_MAX,
	};
	static const std::string TXT_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const std::string BUTTON_A_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const std::string BUTTON_ENTER_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int TUTORIAL_SCREEN_PRIORITY = 20;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CTutorial_Screen(int nPriority = TUTORIAL_SCREEN_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTutorial_Screen()override;
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
	 * @param [in]�^�C�v
	 * @return �`���[�g���A��UI�|�C���^
	 */
	static CTutorial_Screen* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TUTORIAL_UI type);
private:
	TUTORIAL_UI m_UItype;
};
#endif
