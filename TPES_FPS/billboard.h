//=============================================
//
//3DTemplate[billboard.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BILLBOARD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority);
	~CBillboard()override;
	void Draw()override;
};


#endif