//=============================================
//
//3DTemplate[light.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _LIGHT_H_ //これが定義されてないとき

#define _LIGHT_H_
#include "main.h"
#include "input.h"

class CLight
{
public:
	static const int MAX_LIGHT = 3; //ライト最大数
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT]; //ライト情報

};
#endif