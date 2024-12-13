//=============================================
//
//ウルトのマークの表記[ult_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ULT_ICON_H_ //これが定義されてないとき

#define _ULT_ICON_H_
#include "main.h"
#include "object2D.h"

//ウルト表記クラス
class CUltIcon : public CObject2D
{
public:
	static const int ULT_ICON_PRIORITY = 50;  //描画順
	static const D3DXCOLOR START_COLOR;
	enum ULT_TYPE
	{
		ULT_TYPE_MEDIUM,
		ULT_TYPE_MAX,
	};
	CUltIcon(int nPriority = ULT_ICON_PRIORITY);
	~CUltIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CUltIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type);
private:
	float m_AddColor; //色加算の値
};

class CMediumIcon : public CUltIcon
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	CMediumIcon(int nPriority = ULT_ICON_PRIORITY);
	~CMediumIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif