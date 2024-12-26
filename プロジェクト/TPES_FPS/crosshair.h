//=============================================
//
//�N���X�w�A[crosshair.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CROSSHAIR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CROSSHAIR_H_

//=============================================
//�N���X�w�A�N���X
//=============================================
class CCrossHair : public CBillboard
{
public:
	static const std::string CROSSHAIR_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int RETICLE_PRIORITY = 20; //�`�揇

	CCrossHair(int nPriority = RETICLE_PRIORITY);
	~CCrossHair()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�N���X�w�A�쐬
	static CCrossHair* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	D3DXVECTOR3 m_move; //�ړ���
};

#endif