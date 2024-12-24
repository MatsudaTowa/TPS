//=============================================
//
//���S�A�C�R��[death_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _DEATH_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _DEATH_ICON_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CDeathIcon : public CObject2D
{
public:
	static const int PRIORITY = 80;  //�`�揇

	CDeathIcon(int nPriority = PRIORITY);
	~CDeathIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CDeathIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif#pragma once
