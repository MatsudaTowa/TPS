//=============================================
//
//�^�b�N���`���[�W���̃G�t�F�N�g[tackle_charge.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _TACKLE_CHARGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TACKLE_CHARGE_H_

class CTackleCharge : public CBillboard
{
public:
	static const int PRIORITY = 10; //�`�揇
	static const D3DXVECTOR3 SIZE; //�T�C�Y

	CTackleCharge(int nPriority = PRIORITY);
	~CTackleCharge()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CTackleCharge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);

private:
	static const std::string TEXTURE_NAME; //�e�N�X�`���̖��O
};

#endif