//=============================================
//
//�{�X�̓G�̏���[boss_enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOSS_ENEMY_H_
#include "enemy.h"

class CBossEnemy :public CEnemy
{
public:
	CBossEnemy();
	~CBossEnemy() override;
};

#endif