//=============================================
//
//�G�̎c�e���\���uenemy_ammo_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ENEMY_AMMO_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _ENEMY_AMMO_UI_H_
#include "main.h"
#include "object3D.h"
#include "number.h"

//=============================================
//�c�e���\���N���X
//=============================================
class CEnemy_Ammo_UI
{
public:
	static const int NUM_DIGIT = 3;  //����
	static const float DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	CEnemy_Ammo_UI();
	~CEnemy_Ammo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetAmmo_UI(int nAmmo);
	int m_nAmmo; //�e�̐�

	static CEnemy_Ammo_UI*Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);

	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CNumber_3D* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG