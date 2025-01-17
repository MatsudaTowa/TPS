////=============================================
////
////�{�X�̃X�e�[�g�p�^�[��[boss_state.h]
////Auther Matsuda Towa
////
////=============================================
//#ifndef _ENEMY_STATE_H_
//#define _ENEMY_STATE_H_
//
//#include "character_state.h"
//#include "enemy.h"
//
////=============================================
////�O���錾
////=============================================
//class CEnemy;
//
////=============================================
////�{�X�̃X�e�[�g�N���X TODO:�L�����N�^�[�̃X�e�[�g���p������
////=============================================
//class CEnemyState
//{
//public:
//	virtual void Start(CEnemy* enemy);
//	virtual void Chase(CEnemy* enemy);
//	virtual void Stan(CEnemy* enemy);
//	virtual void Wandering(CEnemy* enemy);
//	virtual void Confusion(CEnemy* enemy);
//	virtual void Tackle(CEnemy* enemy);
//	virtual void DrawDebug();
//};
//
////=============================================
////�G�l�~�[�̒ǐՏ��
////=============================================
//class CChaseState : public CEnemyState
//{
//public:
//	CChaseState();
//	~CChaseState();
//	virtual void Chase(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//private:
//	static const int HP_LOW = 30;
//	static const int PLAY_TACKLE_FLAME = 300; //�^�b�N�������s����܂ł̃t���[��
//	int m_PlayTackleCnt; //�^�b�N���܂ł̌v���p
//};
//
////=============================================
////�G�l�~�[�̃X�^�����
////=============================================
//class CBossStanState :public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Stan(CEnemy* enemy);
//	virtual void DrawDebug()override;
//private:
//	static constexpr int STAN_FRAME = 600; //�X�^������
//	int m_StanCnt; //�X�^���v���J�E���g
//};
//
////=============================================
////�G�l�~�[�̜p�j���
////=============================================
//class CWanderingState : public CEnemyState
//{
//public:
//	virtual void Wandering(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//};
//
////=============================================
////�G�l�~�[�̍������
////=============================================
//class CConfusionBossState : public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Confusion(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//private:
//	float m_StartRot;
//	bool m_isRight; //���n��(true:�E false:��)
//};
//
////=============================================
////�G�l�~�[�̃^�b�N�����
////=============================================
//class CTackleState : public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Tackle(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//};
//#endif