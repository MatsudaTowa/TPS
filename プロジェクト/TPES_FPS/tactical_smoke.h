//=============================================
//
//スモーク処理[tactical_somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _TACTICAL_SMOKE_H_ //これが定義されてないとき

#define _TACTICAL_SMOKE_H_

class CTacticalSmoke : public CSmoke
{
public:
	CTacticalSmoke(int nPriority = SMOKE_PRIORITY);
	~CTacticalSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const D3DXCOLOR COLOR;
};

#endif