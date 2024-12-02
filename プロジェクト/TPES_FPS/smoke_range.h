//=============================================
//
//�X���[�N�͈͏���[somoke_range.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_RANGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_RANGE_H_

class CSmokeRange : public CObjectX
{
public:
	static const int SMOKE_RANGE_PRIORITY = 15; //�`�揇

	CSmokeRange(int nPriority = SMOKE_RANGE_PRIORITY);
	~CSmokeRange()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�X���[�N�͈͍쐬
	static CSmokeRange* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//���f���̖��O
	int m_nLife;
};

#endif