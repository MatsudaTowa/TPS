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
	int m_nAmmo; //�X�R�A�̒l
	void SetAmmo_UI(int nAmmo);

private:
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG