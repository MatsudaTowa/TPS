//=============================================
//
//3DTemplate[result.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _RESULT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RESULT_H_
#include "main.h"
#include "scene.h"

class CResult :public CScene
{
public:
	CResult();
	~CResult() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};
#endif