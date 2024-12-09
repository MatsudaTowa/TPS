//=============================================
//
//�G�̃����[�h����UI[enemy_reload_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _ENEMY_RELOAD_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_RELOAD_UI_H_

class CEnemy_Reload_UI : public CBillboard
{
public:
	static const std::string TEXTURE_NAME; //�e�N�X�`���̖��O

	static const int PRIORITY = 24; //�`�揇

	CEnemy_Reload_UI(int nPriority = PRIORITY);
	~CEnemy_Reload_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CEnemy_Reload_UI* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);

private:
};

#endif