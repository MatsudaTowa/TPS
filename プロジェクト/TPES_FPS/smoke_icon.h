//=============================================
//
//�X���[�N�̕\�L[smoke_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SMOKE_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_ICON_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CSmokeIcon : public CObject2D
{
public:
	static const int SMOKE_ICON_PRIORITY = 21;  //�`�揇

	CSmokeIcon(int nPriority = SMOKE_ICON_PRIORITY);
	~CSmokeIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CSmokeIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif