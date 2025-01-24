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
#include "player.h"
#include "keyboard_UI.h"

class CPlayer;
class CUltIcon;
//=============================================
//�c�e���\���N���X
//=============================================
class CUlt_UI
{
public:
	CUlt_UI();
	~CUlt_UI();
	HRESULT Init(CPlayer* player);
	void Uninit();
	void Update();
	void SetCurrentUlt_UI(CPlayer* player);

	void Reset();

private:
	static const float PARCENT_DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	static const D3DXVECTOR3 ICON_POS; //�E���g�A�C�R���̈ʒu
	static const D3DXVECTOR2 ICON_SIZE; //�E���g�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 KEY_UI_POS; //�L�[�{�[�h��UI�̈ʒu
	static const D3DXVECTOR2 KEY_UI_SIZE; //�L�[�{�[�h��UI�̃T�C�Y

	D3DXVECTOR3 m_PercentPos;
	CUltIcon* m_pIcon;
	CKeyboard_UI* m_pKeyboard_UI;
};

#endif // DEBUG