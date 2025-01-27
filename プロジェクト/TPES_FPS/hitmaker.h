//=============================================
//
//�q�b�g�}�[�J�[[hitmaker.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _HITMAKER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _HITMAKER_H_

//=============================================
//�N���X�w�A�N���X
//=============================================
class CHitMaker : public CBillboard
{
public:
	static const std::string HITMARKER_DOT_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int RETICLE_PRIORITY = 28; //�`�揇

	static const int HITMARKER_LIFE = 30; //�̗�

	CHitMaker(int nPriority = RETICLE_PRIORITY);
	~CHitMaker()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void HitColor(D3DXCOLOR col);

	//�N���X�w�A�쐬
	static CHitMaker* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	int m_nLife;
};

#endif