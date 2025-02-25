//=============================================
//
//2DUI�̕\�L[UI_2D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _UI_2D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _UI_2D_H_
#include "main.h"
#include "object2D.h"

//2DUI�̕\�L�N���X
class CUI_2D : public CObject2D
{
public:
	static const int PRIORITY = 20;  //�`�揇

	CUI_2D(int nPriority = PRIORITY);
	~CUI_2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	bool m_isDraw;
};
#endif