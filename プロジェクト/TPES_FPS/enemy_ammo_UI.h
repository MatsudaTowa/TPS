//=============================================
//
//敵の残弾数表示「enemy_ammo_UI.h」
// Author松田永久
//
//=============================================
#ifndef _ENEMY_AMMO_UI_H_ //これが定義されてないとき
#define _ENEMY_AMMO_UI_H_
#include "main.h"
#include "object3D.h"
#include "number.h"

//=============================================
//残弾数表示クラス
//=============================================
class CEnemy_Ammo_UI
{
public:
	static const int NUM_DIGIT = 3;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CEnemy_Ammo_UI();
	~CEnemy_Ammo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetAmmo_UI(int nAmmo);
	int m_nAmmo; //弾の数

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