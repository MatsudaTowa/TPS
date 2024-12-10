//=============================================
//
//プレイヤーのUIの枠[player_UI_box.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //これが定義されてないとき

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//プレイヤーのUIの枠クラス
class CPlayerUIBox : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int UI_BOX_PRIORITY = 30;  //描画順
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	~CPlayerUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col);
private:
};
#endif