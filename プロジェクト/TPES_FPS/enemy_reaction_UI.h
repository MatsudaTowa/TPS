//=============================================
//
//敵のリアクションのUI[enemy_reaction_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _ENEMY_REACTION_UI_H_ //これが定義されてないとき

#define _ENEMY_REACTION_UI_H_

class CEnemy_Reaction_UI : public CBillboard
{
public:
	static const int PRIORITY = 24; //描画順

	enum REACTION
	{
		REACTION_RELOAD = 0,
		REACTION_WANDERING,
		REACTION_STAN,
	};

	CEnemy_Reaction_UI(int nPriority = PRIORITY);
	~CEnemy_Reaction_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CEnemy_Reaction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, REACTION type);

private:
};

#endif