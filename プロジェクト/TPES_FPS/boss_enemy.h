//=============================================
//
//ƒ{ƒX‚Ì“G‚Ìˆ—[boss_enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _BOSS_ENEMY_H_
#include "enemy.h"

class CBossEnemy :public CEnemy
{
public:
	CBossEnemy();
	~CBossEnemy() override;
};

#endif