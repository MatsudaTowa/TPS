//=============================================
//
//�E���g�G�t�F�N�g�uult_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ULT_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_EFFECT_H_
#include "main.h"
#include "object3D.h"

//�E���g�G�t�F�N�g�N���X
class CUltEffect : public CObject3D
{
public:

	static const int PRIORITY = 12; //�`�揇

	CUltEffect(int nPriority = PRIORITY);
	~CUltEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CUltEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif