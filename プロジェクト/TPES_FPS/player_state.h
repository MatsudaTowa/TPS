//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "player_test.h"
#include "ult.h"

//=============================================
//�O���錾
//=============================================
class CPlayer_test;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CPlayerState
{
public:
	virtual void Default(CPlayer_test* player);
	virtual void Ult(CPlayer_test* player);
};

//=============================================
//�L�����N�^�[�̒ʏ���
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CPlayer_test* player)override;
};

//=============================================
//�L�����N�^�[�̃E���g���
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CPlayer_test* player) override;
};

#endif // !_PLAYER_STATE_H
