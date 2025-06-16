//=============================================
//
//�X���[�N�󋵕\���usmoke_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SMOKE_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SMOKE_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "active_player.h"
#include "player_UI_box.h"
#include "smoke_icon.h"
#include "keyboard_UI.h"

//=============================================
//�X���[�NUI�N���X
//=============================================
class CSmoke_UI
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CSmoke_UI();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSmoke_UI();
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
	 * @brief ���݂̃X���[�NUI�ݒ�
	 * @param [in]�v���C���[�̃|�C���^
	 */
	void SetCurrentSmoke_UI(CActivePlayer* player);

	/**
	 * @brief �����ݒ�
	 * @param [in]�l
	 */
	void SetNumber(int nParcent);

	/**
	 * @brief �Q�[�W���Z�b�g
	 */
	void Reset();

private:
	static const int NUM_DIGIT = 1;  //����
	static constexpr float DIGIT_SHIFT = 35.0f;  //�����Ƃɍ��W�����炷

	static const D3DXVECTOR3 BOX_POS; //�g�̈ʒu
	static const D3DXVECTOR2 BOX_SIZE; //�g�̃T�C�Y

	static const D3DXVECTOR3 ICON_POS; //�X���[�N�A�C�R���̈ʒu
	static const D3DXVECTOR2 ICON_SIZE; //�X���[�N�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 NUMBER_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUMBER_SIZE; //�����̃T�C�Y

	static const D3DXVECTOR3 KEY_UI_POS; //�L�[�{�[�h��UI�̈ʒu
	static const D3DXVECTOR2 KEY_UI_SIZE; //�L�[�{�[�h��UI�̃T�C�Y

	int m_NumSmoke;
	D3DXVECTOR3 m_SmokePos;
	CSmokeIcon* m_pIcon;
	CPlayerUIBox* m_pUIBox;
	CKeyboard_UI* m_pkeyboard_UI;
	CNumber_2D* m_pCurrentSmoke[NUM_DIGIT];
};

#endif