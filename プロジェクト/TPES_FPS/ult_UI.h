//=============================================
//
//ult状況表示「ult_UI.h」
// Author松田永久
//
//=============================================
#ifndef _ULT_UI_H_ //これが定義されてないとき
#define _ULT_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_test.h"
#include "ult_icon.h"

class CPlayer_test;
//=============================================
//残弾数表示クラス
//=============================================
class CUlt_UI
{
public:
	CUlt_UI();
	~CUlt_UI();
	HRESULT Init(CPlayer_test* player);
	void Uninit();
	void Update();
	void SetCurrentUlt_UI(CPlayer_test* player);

	void SetNumber(int nParcent);

	void Reset();

private:
	static const int NUM_DIGIT = 3;  //桁数
	static const float PARCENT_DIGIT_SHIFT;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 ICON_POS; //ウルトアイコンの位置
	static const D3DXVECTOR2 ICON_SIZE; //ウルトアイコンのサイズ

	static const D3DXVECTOR3 PARCENT_POS; //ウルトパーセントの位置
	static const D3DXVECTOR2 PARCENT_SIZE; //ウルトパーセントのサイズ

	D3DXVECTOR3 m_PercentPos;
	CUltIcon* m_pIcon;
	CNumber_2D* m_pParcent[NUM_DIGIT];
};

#endif // DEBUG