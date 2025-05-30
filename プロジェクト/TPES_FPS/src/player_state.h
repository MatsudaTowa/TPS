//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "ult.h"

//=============================================
//�O���錾
//=============================================
class CActivePlayer;

//=============================================
//�L�����N�^�[�̃X�e�[�g�N���X
//=============================================
class CPlayerState
{
public:
	virtual void Default(CActivePlayer* player);
	virtual void Ult(CActivePlayer* player);
	virtual void Avoidance(CActivePlayer* player);
	virtual void Blown(CActivePlayer* player);
};

//=============================================
//�L�����N�^�[�̒ʏ���
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CActivePlayer* player)override;
};

//=============================================
//�L�����N�^�[�̃E���g���
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CActivePlayer* player) override;
};

//=============================================
//�L�����N�^�[�̉�����
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	virtual void Avoidance(CActivePlayer* player) override;
};

//=============================================
//�L�����N�^�[�̐�����΂�����
//=============================================
class CBlownState : public CPlayerState
{
public:
	CBlownState();
	virtual void Blown(CActivePlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
