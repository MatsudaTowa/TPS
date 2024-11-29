//=============================================
//
//�X���[�N����[somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_H_

class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //�e�N�X�`���̖��O
	static const int SMOKE_LIFE = 600; //�X���[�N�̎�������

	static const int SMOKE_PRIORITY = 24; //�`�揇

	CSmoke(int nPriority = SMOKE_PRIORITY);
	~CSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void ColisionRange();
	void Draw()override;

	//�X���[�N�쐬
	static CSmoke* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,D3DXVECTOR3 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	int m_nLife;
	D3DXVECTOR3 m_move;
	//TODO:����old������O�O
	D3DXVECTOR3 m_oldpos;
};

#endif