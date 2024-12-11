//=============================================
//
//残弾数表示「ammo_UI.h」
// Author松田永久
//
//=============================================
#ifndef _AMMO_UI_H_ //これが定義されてないとき
#define _AMMO_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_test.h"
#include "player_UI_box.h"

//=============================================
//残弾数表示クラス
//=============================================
class CAmmo_UI
{
public:
	static const int NUM_DIGIT = 2;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CAmmo_UI();
	~CAmmo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nAmmo; //残弾数の値
	void SetAmmo_UI(int nAmmo);

private:
	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ
	D3DXVECTOR3 m_pos;
	CPlayerUIBox* m_pUIBox;
	CNumber_2D* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG