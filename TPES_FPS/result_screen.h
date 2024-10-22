//=============================================
//
//3DTemplate[result_screen.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _RESULT_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RESULT_SCREEN_H_
#include "main.h"
#include "object2D.h"

//�����_���[�N���X
class CResult_Screen : public CObject2D
{
public:
	static const int RESULT_SCREEN_PRIORITY = 30;  //�`�揇
	CResult_Screen(int nPriority = RESULT_SCREEN_PRIORITY);
	~CResult_Screen()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CResult_Screen* Create(D3DXVECTOR3 pos);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif