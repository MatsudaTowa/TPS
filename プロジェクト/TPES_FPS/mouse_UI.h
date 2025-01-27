//=============================================
//
//�}�E�XUI�̕\�L[mouse_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MOUSE_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_UI_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CMouse_UI : public CObject2D
{
public:
	static const int PRIORITY = 27;  //�`�揇

	enum MOUSE_TYPE
	{
		MOUSE_R = 0,
		MOUSE_L,
		MOUSE_MAX
	};

	CMouse_UI(int nPriority = PRIORITY);
	~CMouse_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CMouse_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, MOUSE_TYPE type);
private:
	static const std::string TEXTURE_NAME[MOUSE_MAX];	//�e�N�X�`���̖��O
	MOUSE_TYPE m_type;
};
#endif