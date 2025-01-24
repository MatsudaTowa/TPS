//=============================================
//
//�`���[�g���A���\���ututorial_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _TUTORIAL_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _TUTORIAL_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "action_UI.h"
#include "keyboard_UI.h"
#include "mouse_UI.h"

class CPlayer;
//=============================================
//�`���[�g���A��UI�N���X
//=============================================
class CTutorial_UI
{
public:
	CTutorial_UI();
	~CTutorial_UI();
	HRESULT Init();
	void Uninit();
	void Update();
private:
	static const float PARCENT_DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	static const D3DXVECTOR3 RELOAD_TXT_POS; //�����[�h�A�C�R���̈ʒu
	static const D3DXVECTOR2 RELOAD_TXT_SIZE; //�����[�h�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 SHOT_MODE_TXT_POS; //�V���b�g�̈ʒu
	static const D3DXVECTOR2 SHOT_MODE_TXT_SIZE; //�V���b�g�̃T�C�Y

	static const D3DXVECTOR3 SHOT_TXT_POS; //�V���b�g�̈ʒu
	static const D3DXVECTOR2 SHOT_TXT_SIZE; //�V���b�g�̃T�C�Y

	static const D3DXVECTOR3 RELOAD_TXT_POS; //�����[�h�A�C�R���̈ʒu
	static const D3DXVECTOR2 RELOAD_TXT_SIZE; //�����[�h�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 KEY_UI_POS; //�L�[�{�[�h��UI�̈ʒu
	static const D3DXVECTOR2 KEY_UI_SIZE; //�L�[�{�[�h��UI�̃T�C�Y

	static const D3DXVECTOR3 MOUSE_SHOT_MODE_UI_POS; //�}�E�X��UI�̈ʒu
	static const D3DXVECTOR2 MOUSE_UI_SIZE; //�}�E�X��UI�̃T�C�Y

	static const D3DXVECTOR3 MOUSE_SHOT_UI_POS; //�}�E�X��UI�̈ʒu
	
	CAction_UI* m_pReloadUI;
	CAction_UI* m_pShotModeUI;
	CAction_UI* m_pShotUI;
	CKeyboard_UI* m_pKeyboardReload_UI;
	CMouse_UI* m_pMouseshot_UI;
	CMouse_UI* m_pMouseshotmode_UI;
};

#endif // DEBUG