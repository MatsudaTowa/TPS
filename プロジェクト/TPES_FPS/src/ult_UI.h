//=============================================
//
//ult�󋵕\���uult_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ULT_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _ULT_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "keyboard_UI.h"

//=============================================
// �O���錾
//============================================
class CActivePlayer;
class CUltIcon;

//=============================================
//�c�e���\���N���X
//=============================================
class CUlt_UI
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CUlt_UI();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUlt_UI();
	/**
	 * @brief ������
	 * @param [in]�v���C���[�̃|�C���^
	 * @return ����������
	 */
	HRESULT Init(CActivePlayer* player);
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
	/**
	 * @brief ���݂̃E���gUI�ݒ�
	 * @param [in]�v���C���[�̃|�C���^
	 */
	void SetCurrentUlt_UI(CActivePlayer* player);

	/**
	 * @brief ���Z�b�g�֐�
	 */
	void Reset();

private:
	static constexpr float PARCENT_DIGIT_SHIFT = 18.0f;  //�����Ƃɍ��W�����炷

	static const D3DXVECTOR3 ICON_POS; //�E���g�A�C�R���̈ʒu
	static const D3DXVECTOR2 ICON_SIZE; //�E���g�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 KEY_UI_POS; //�L�[�{�[�h��UI�̈ʒu
	static const D3DXVECTOR2 KEY_UI_SIZE; //�L�[�{�[�h��UI�̃T�C�Y

	D3DXVECTOR3 m_PercentPos;
	CUltIcon* m_pIcon;
	CKeyboard_UI* m_pKeyboard_UI;
};

#endif // DEBUG