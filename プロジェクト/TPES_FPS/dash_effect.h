//=============================================
//
//�_�b�V�����ɃL�����N�^�[�̑O���ɏo���G�t�F�N�g[dash_effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _DASH_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _DASH_EFFECT_H_
#include "main.h"
#include "objectX.h"

class CDashEffect : public CObjectX
{
public:
	static const char* MODEL_NAME;	//���f���̖��O

	static const int PRIORITY = 11; //�`�揇

	CDashEffect(int nPriority = PRIORITY);
	~CDashEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�u���b�N�쐬
	static CDashEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
};
#endif