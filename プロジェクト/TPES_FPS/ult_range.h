//=============================================
//
//ウルト範囲処理[ult_range.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"

#ifndef _ULT_RANGE_H_ //これが定義されてないとき

#define _ULT_RANGE_H_

class CUltRange
{
public:

	CUltRange();
	~CUltRange();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//ウルト範囲作成
	static CUltRange* Create(D3DXVECTOR3 pos);

private:
	static const int LIFE = 30;
	static const int MAX_DAMAGE = 20;
	static const D3DXVECTOR3 SIZE;
	int m_nLife;
};

#endif