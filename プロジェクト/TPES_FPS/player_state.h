//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "player.h"
#include "ult.h"

//=============================================
//�O���錾
//=============================================
class CPlayer;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CPlayerState
{
public:
	virtual void Default(CPlayer* player);
	virtual void Ult(CPlayer* player);
	virtual void Avoidance(CPlayer* player);
	virtual void Blown(CPlayer* player);
};

//=============================================
//�L�����N�^�[�̒ʏ���
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CPlayer* player)override;
};

//=============================================
//�L�����N�^�[�̃E���g���
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CPlayer* player) override;
};

//=============================================
//�L�����N�^�[�̉�����
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	virtual void Avoidance(CPlayer* player) override;
};

//=============================================
//�L�����N�^�[�̐�����΂�����
//=============================================
class CBlownState : public CPlayerState
{
public:
	CBlownState();
	virtual void Blown(CPlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
