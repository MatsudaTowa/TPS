//=============================================
//
//�e�ushadow.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SHADOW_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//�����_���[�N���X
class CShadow : public CObject3D
{
public:

	static const int SHADOW_PRIORITY = 9; //�`�揇

	CShadow(int nPriority = SHADOW_PRIORITY);
	~CShadow()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif