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
//�{�X�̃X�e�[�g�N���X TODO:�L�����N�^�[�̃X�e�[�g���p������
//=============================================
class CBossState
{
public:
	CBossState();
	virtual ~CBossState();
	virtual void Start(CBossEnemy* boss);
	virtual void Chase(CBossEnemy* boss);
	virtual void Stan(CBossEnemy* boss);
	virtual void Wandering(CBossEnemy* boss);
	virtual void Confusion(CBossEnemy* boss);
	virtual void Tackle(CBossEnemy* boss);
	virtual void Search(CBossEnemy* boss);
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
	static const int HP_LOW = 30;
	static const int PLAY_TACKLE_FLAME = 300; //�^�b�N�������s����܂ł̃t���[��
	int m_PlayTackleCnt; //�^�b�N���܂ł̌v���p
};

//=============================================
//�G�l�~�[�̃X�^�����
//=============================================
class CBossStanState :public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	virtual void Stan(CBossEnemy* boss);
	virtual void DrawDebug()override;
private:
	static constexpr int STAN_FRAME = 600; //�X�^������
	int m_StanCnt; //�X�^���v���J�E���g
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
//�G�l�~�[�̍������
//=============================================
class CConfusionBossState : public CBossState
{
public:
	CConfusionBossState();
	~CConfusionBossState();
	void Start(CBossEnemy* boss) override;
	virtual void Confusion(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	float m_StartRot;
	bool m_isRight; //���n��(true:�E false:��)
	CEnemy_Reaction_UI* m_pReaction;
};

//=============================================
//�G�l�~�[�̃^�b�N�����
//=============================================
class CTackleState : public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	virtual void Tackle(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};

//=============================================
//�G�l�~�[�̃v���C���[��T�����
//=============================================
class CSearchState : public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	virtual void Search(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	D3DXVECTOR3 m_TargetPos;
};
#endif