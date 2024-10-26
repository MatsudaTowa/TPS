//=============================================
//
//3DTemplate[light.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _LIGHT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _LIGHT_H_
#include "main.h"
#include "input.h"

class CLight
{
public:
	static const int MAX_LIGHT = 3; //���C�g�ő吔
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT]; //���C�g���

};
#endif