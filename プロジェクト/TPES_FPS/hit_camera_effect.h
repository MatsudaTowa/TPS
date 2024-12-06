//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//体力表示クラス
//=============================================
class CHitCameraEffect:public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int PRIORITY = 30; //描画順

	CHitCameraEffect(int nPriority = PRIORITY);
	~CHitCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CHitCameraEffect* Create(D3DXVECTOR3 pos);

	void SubAlpha();

	float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	float m_alpha; //アルファ値
};

#endif // _HIT_CAMERA_EFFECT_H_