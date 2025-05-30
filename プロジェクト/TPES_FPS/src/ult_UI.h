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
#include "keyboard_UI.h"

//=============================================
// 前方宣言
//============================================
class CActivePlayer;
class CUltIcon;

//=============================================
//残弾数表示クラス
//=============================================
class CUlt_UI
{
public:
	CUlt_UI();
	~CUlt_UI();
	HRESULT Init(CActivePlayer* player);
	void Uninit();
	void Update();
	void SetCurrentUlt_UI(CActivePlayer* player);

	void Reset();

private:
	static constexpr float PARCENT_DIGIT_SHIFT = 18.0f;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 ICON_POS; //ウルトアイコンの位置
	static const D3DXVECTOR2 ICON_SIZE; //ウルトアイコンのサイズ

	static const D3DXVECTOR3 KEY_UI_POS; //キーボードのUIの位置
	static const D3DXVECTOR2 KEY_UI_SIZE; //キーボードのUIのサイズ

	D3DXVECTOR3 m_PercentPos;
	CUltIcon* m_pIcon;
	CKeyboard_UI* m_pKeyboard_UI;
};

#endif // DEBUG