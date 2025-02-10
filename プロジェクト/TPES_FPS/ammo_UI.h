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
#include "player.h"
#include "player_UI_box.h"

//=============================================
//�c�e���\���N���X
//=============================================
class CAmmo_UI
{
public:
	CAmmo_UI();
	~CAmmo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	//TODO:���̏������ł�������inline�W�J�ł��Ȃ��\����
	void SetCurrentAmmo_UI(int nAmmo);
	void SetDefaultAmmo_UI(int nAmmo);

private:
	static const int NUM_DIGIT = 2;  //����
	static const float CURRENT_AMMO_DIGIT_SHIFT;  //�����Ƃɍ��W�����炷
	static const float DEFAULT_AMMO_DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	static const D3DXVECTOR3 BOX_POS; //�g�̈ʒu
	static const D3DXVECTOR2 BOX_SIZE; //�g�̃T�C�Y

	static const D3DXVECTOR3 CURRENT_AMMO_POS; //���݂̒e���̈ʒu
	static const D3DXVECTOR2 CURRENT_AMMO_SIZE; //���݂̒e���̃T�C�Y

	static const D3DXVECTOR3 DEFAULT_AMMO_POS; //�ʏ�̒e���̈ʒu
	static const D3DXVECTOR2 DEFAULT_AMMO_SIZE; //�ʏ�̒e���̃T�C�Y

	int m_nDefaultAmmo; //�c�e���̒l
	D3DXVECTOR3 m_CurrentAmmoPos;
	D3DXVECTOR3 m_DefaultAmmoPos;
	CPlayerUIBox* m_pUIBox;
	CNumber_2D* m_pCurrentAmmo[NUM_DIGIT];
	CNumber_2D* m_pDefaultAmmo[NUM_DIGIT];
};

#endif // DEBUG