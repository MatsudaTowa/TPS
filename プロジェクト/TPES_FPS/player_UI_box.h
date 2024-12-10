//=============================================
//
//�v���C���[��UI�̘g[player_UI_box.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//�v���C���[��UI�̘g�N���X
class CPlayerUIBox : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int UI_BOX_PRIORITY = 30;  //�`�揇
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	~CPlayerUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col);
private:
};
#endif