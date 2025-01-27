//=============================================
//
//�u�����N�̕\�L[blink_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLINK_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BLINK_ICON_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CBlinkIcon : public CObject2D
{
public:
	static const int ICON_PRIORITY = 21;  //�`�揇

	CBlinkIcon(int nPriority = ICON_PRIORITY);
	~CBlinkIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlinkIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif