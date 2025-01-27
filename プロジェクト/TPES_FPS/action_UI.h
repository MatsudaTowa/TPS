//=============================================
//
//�A�N�V����UI�̕\�L[action_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ACTION_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ACTION_UI_H_
#include "main.h"
#include "object2D.h"

//�X���[�N�̕\�L�N���X
class CAction_UI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //�`�揇

	enum ACTION_TYPE
	{
		ACTION_MOVE = 0,
		ACTION_SHOTMODE,
		ACTION_SHOT,
		ACTION_RELOAD,
		ACTION_ULT,
		ACTION_SMOKE,
		ACTION_MAX
	};

	CAction_UI(int nPriority = PRIORITY);
	~CAction_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CAction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ACTION_TYPE type);
private:
	static const std::string TEXTURE_NAME[ACTION_MAX];	//�e�N�X�`���̖��O
	ACTION_TYPE m_type;
};
#endif