//=============================================
//
//�E���g�͈͏���[ult_range.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"

#ifndef _ULT_RANGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

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

	//�E���g�͈͍쐬
	static CUltRange* Create(D3DXVECTOR3 pos);

private:
	static const int LIFE = 30;
	static const int MAX_DAMAGE = 20;
	static const D3DXVECTOR3 SIZE;
	int m_nLife;
};

#endif