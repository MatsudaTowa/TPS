//=============================================
//
//�Z���^�[�h�b�g[centerdot.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CENTERDOT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CENTERDOT_H_

//=============================================
//�Z���^�[�h�b�g�N���X
//=============================================
class CCenterDot : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 19; //�`�揇

	CCenterDot(int nPriority = RETICLE_PRIORITY);
	~CCenterDot()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�Z���^�[�h�b�g�쐬
	static CCenterDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CENTERDOT_TEXTURE_NAME;	//�e�N�X�`���̖��O
};

#endif