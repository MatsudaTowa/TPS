//=============================================
//
//�^�C�g����UI[title_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
// �^�C�g����ʃN���X
//=============================================
class CTitle_Screen : public CObject2D
{
public: 
	enum TITLE_UI
	{
		UI_NONE = 0,
		UI_TITLE_ROGO,
		UI_TITLE_PRESS_BUTTON,
		UI_TITLE_MAX,
	};
	static const std::string ROGO_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const std::string BUTTON_A_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const std::string BUTTON_ENTER_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int TITLE_SCREEN_PRIORITY = 10;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CTitle_Screen(int nPriority = TITLE_SCREEN_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTitle_Screen()override;
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
	 * @return �^�C�g��UI�|�C���^
	 */
	static CTitle_Screen* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,TITLE_UI type);
private:
	TITLE_UI m_UItype;
};
#endif