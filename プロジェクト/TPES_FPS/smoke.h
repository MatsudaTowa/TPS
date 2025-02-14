//=============================================
//
//スモーク処理[somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //これが定義されてないとき

#define _SMOKE_H_

class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //テクスチャの名前
	static const int SMOKE_LIFE = 300; //スモークの持続時間

	static const int MOVE_X_MAX = 3; //スモークの移動量の最大値_X
	static const int MOVE_X_MIN = -3; //スモークの移動量の最小値_X

	static const int MOVE_Y_MAX = 6; //スモークの移動量の最大値_Y
	static const int MOVE_Y_MIN = 1; //スモークの移動量の最小値_Y

	static const int MOVE_Z_MAX = 1; //スモークの移動量の最大値_Z
	static const int MOVE_Z_MIN = 0; //スモークの移動量の最小値_Z

	static const D3DXVECTOR3 SIZE; //スモークのサイズ

	static const int SMOKE_PRIORITY = 10; //描画順

	enum SMOKE_TYPE
	{
		SMOKE_TYPE_TACTICAL	= 0,
		SMOKE_TYPE_BROKEN
	};

	CSmoke(int nPriority = SMOKE_PRIORITY);
	~CSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//スモーク作成
	static CSmoke* Create(D3DXVECTOR3 pos, SMOKE_TYPE type);

private:
	int m_nLife;
	D3DXVECTOR3 m_move;
	//TODO:何個old作るつもり＾＾
	D3DXVECTOR3 m_oldpos;
};

#endif