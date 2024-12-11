//=============================================
//
//�c�e���\���uammo_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _AMMO_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _AMMO_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_test.h"
#include "player_UI_box.h"

//=============================================
//�c�e���\���N���X
//=============================================
class CAmmo_UI
{
public:
	static const int NUM_DIGIT = 2;  //����
	static const float DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	CAmmo_UI();
	~CAmmo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nAmmo; //�c�e���̒l
	void SetAmmo_UI(int nAmmo);

private:
	static const D3DXVECTOR3 BOX_POS; //�g�̈ʒu
	static const D3DXVECTOR2 BOX_SIZE; //�g�̃T�C�Y

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y
	D3DXVECTOR3 m_pos;
	CPlayerUIBox* m_pUIBox;
	CNumber_2D* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG