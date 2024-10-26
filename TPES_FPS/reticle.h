//=============================================
//
//���e�B�N��[reticle.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _RETICLE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RETICLE_H_

//=============================================
//���e�B�N���N���X
//=============================================
class CReticle : public CBillboard
{
public:
	static const std::string RETICLE_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int RETICLE_PRIORITY = 30; //�`�揇

	CReticle(int nPriority = RETICLE_PRIORITY);
	~CReticle()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�e�쐬
	static CReticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	void Move();
private:
	D3DXVECTOR3 m_move; //�ړ���
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};

#endif