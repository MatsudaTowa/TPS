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

	//�E���g�͈͍쐬
	static CUltRange* Create(D3DXVECTOR3 pos);

	int& GetLife()
	{
		return m_nLife;
	}
private:
	static const int LIFE = 10;
	static const int MAX_DAMAGE = 20;
	static const float RADIUS;
	D3DXVECTOR3 m_pos;
	int m_nLife;
};

#endif