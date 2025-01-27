//=============================================
//
//ult�����܂����Ƃ��ɃA�C�R������o���G�t�F�N�g[ult_icon_effect.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "Object2D_anim.h"

#ifndef _ULT_ICON_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_ICON_EFFECT_H_

class CUltIconEffect : public CObject2D_Anim
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int PRIORITY = 20; //�`�揇
	static const int TEX_SPLIT_X = 4; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y = 1; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME = 10; //�A�j���[�V�����t���[����

	CUltIconEffect(int nPriority = PRIORITY);
	~CUltIconEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�e�쐬
	static CUltIconEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
};
#endif