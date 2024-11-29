//=============================================
//
//�{�X�̃X�e�[�g�p�^�[��[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_

#include "character_state.h"
#include "boss_enemy.h"

//=============================================
//�O���錾
//=============================================
class CBossEnemy;

//=============================================
//�{�X�̃X�e�[�g�N���X
//=============================================
class CBossState
{
public:
	virtual void Chase(CBossEnemy* boss);
	virtual void Wandering(CBossEnemy* boss);
	virtual void Tackle(CBossEnemy* boss);
	virtual void DrawDebug();
};

//=============================================
//�G�l�~�[�̒ǐՏ��
//=============================================
class CChaseState : public CBossState
{
public:
	CChaseState();
	~CChaseState();
	virtual void Chase(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	static const int HP_LOW = 20;
	static const int PLAY_TACKLE_FLAME = 600; //�^�b�N�������s����܂ł̃t���[��
	int m_PlayTackleCnt; //�^�b�N���܂ł̌v���p
};

//=============================================
//�G�l�~�[�̜p�j���
//=============================================
class CWanderingState : public CBossState
{
public:
	virtual void Wandering(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};

//=============================================
//�G�l�~�[�̃^�b�N�����
//=============================================
class CTackleState : public CBossState
{
public:
	virtual void Tackle(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};
#endif