//=============================================
//
//タイトルのUI[title_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_SCREEN_H_ //これが定義されてないとき

#define _TITLE_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
// タイトル画面クラス
//=============================================
class CTitle_Screen : public CObject2D
{
public: 
	enum TITLE_UI
	{
		UI_NONE = 0,
		UI_TITLE_ROGO,
		UI_TITLE_PRESS_BUTTON,
		UI_TITLE_MAX,
	};
	static const std::string ROGO_TEXTURE_NAME;	//テクスチャの名前
	static const std::string BUTTON_A_TEXTURE_NAME;	//テクスチャの名前
	static const std::string BUTTON_ENTER_TEXTURE_NAME;	//テクスチャの名前
	static const int TITLE_SCREEN_PRIORITY = 10;  //描画順
	CTitle_Screen(int nPriority = TITLE_SCREEN_PRIORITY);
	~CTitle_Screen()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Screen* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,TITLE_UI type);
private:
	TITLE_UI m_UItype;
};
#endif