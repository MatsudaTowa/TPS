//=============================================
//
//スモーク処理[broken_somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _BROKEN_SMOKE_H_ //これが定義されてないとき

#define _BROKEN_SMOKE_H_

class CBrokenSmoke : public CSmoke
{
public:
	CBrokenSmoke(int nPriority = SMOKE_PRIORITY);
	~CBrokenSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const D3DXCOLOR COLOR;
};

#endif