//=============================================
//
//�L�[�{�[�hUI�̕\�L[keyboard_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _KEYBOARD_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _KEYBOARD_UI_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CKeyboard_UI : public CObject2D
{
public:
	static const int PRIORITY = 26;  //�`�揇

	enum KEY_TYPE
	{
		KEY_W = 0,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_Q,
		KEY_X,
		KEY_R,
		KEY_LSHIFT,
		KEY_MAX
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CKeyboard_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CKeyboard_UI()override;
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
	 * @param [in]�L�[
	 * @return �L�[�{�[�hUI�̃|�C���^
	 */
	static CKeyboard_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, KEY_TYPE key);
private:
	static const std::string TEXTURE_NAME[KEY_MAX];	//�e�N�X�`���̖��O
	KEY_TYPE m_type;
};
#endif