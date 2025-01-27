//=============================================
//
//ゲージ管理[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //これが定義されてないとき

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ゲージクラス
//=============================================
class CGauge_2D : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	enum GAUGE_TYPE
	{
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_MAX,
	};
	static const int GAUGE_PRIORITY = 28;  //描画順
	static const float MAX_GAUGE_WIDE;  //ゲージの最大値
	CGauge_2D(int nPriority = GAUGE_PRIORITY);
	~CGauge_2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetGauge(D3DXVECTOR2 size);
	static CGauge_2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col);
private:
	GAUGE_TYPE m_type;
};

//=============================================
//体力ゲージクラス
//=============================================
class CGauge_Life : public CGauge_2D
{
public:
	CGauge_Life(int nPriority = GAUGE_PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif