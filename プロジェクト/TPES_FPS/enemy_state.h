//=============================================
//
//�G�l�~�[�̃X�e�[�g�p�^�[��[enemy_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_STATE_H_
#define _ENEMY_STATE_H_

#include "character_state.h"
#include "enemy.h"

//=============================================
//�O���錾
//=============================================
class CEnemy;

//=============================================
//�G�l�~�[�̃X�e�[�g�N���X
//=============================================
class CEnemyState : public CCharacterState
{
public:
	virtual void Move(CCharacter* character)override;
	virtual void Wandering(CEnemy* enemy);
};

//=============================================
//�G�l�~�[�̈ړ����(�G���G�̂�) TODO:�Ȃ�X�e�[�g�p�^�[���g�݊����悤
//=============================================
class CEnemyMoveState : public CEnemyState
{
public:
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
