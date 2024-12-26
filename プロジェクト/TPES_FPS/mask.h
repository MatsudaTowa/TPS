//=============================================
//
//�}�X�N����[mask.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MASK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MASK_H_
#include "main.h"
#include "scene.h"
#include "object2D.h"

//�}�X�N�N���X
class CMask : public CObject2D
{
public:
	static const int MASK_PRIORITY = 12;  //�`�揇

	CMask(int nPriority = MASK_PRIORITY);
	~CMask()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CMask* Create();
private:
};
#endif