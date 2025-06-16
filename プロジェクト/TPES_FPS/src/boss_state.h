//=============================================
//
//�{�X�̃X�e�[�g�p�^�[��[boss_state.h]
//Author Matsuda Towa
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
	/**
	 * @brief �R���X�g���N�^
	 */
	CBossState();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CBossState();
	/**
	 * @brief �ŏ��ɌĂ΂��֐�
	 * @param �{�X�̃|�C���^
	 */
	virtual void Start(CBossEnemy* boss);
	/**
	 * @brief �Ō�ɌĂ΂��֐�
	 * @param �{�X�̃|�C���^
	 */
	virtual void End(CBossEnemy* boss);
	/**
	 * @brief �ǐ�
	 * @param �{�X�̃|�C���^
	 */
	virtual void Chase(CBossEnemy* boss);
	/**
	 * @brief �X�^��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Stan(CBossEnemy* boss);
	/**
	 * @brief �p�j
	 * @param �{�X�̃|�C���^
	 */
	virtual void Wandering(CBossEnemy* boss);
	/**
	 * @brief ����
	 * @param �{�X�̃|�C���^
	 */
	virtual void Confusion(CBossEnemy* boss);
	/**
	 * @brief �^�b�N��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Tackle(CBossEnemy* boss);
	/**
	 * @brief �T��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Search(CBossEnemy* boss);
	/**
	 * @brief �\��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Rampage(CBossEnemy* boss);
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug();
};

//=============================================
//�G�l�~�[�̒ǐՏ��
//=============================================
class CChaseState : public CBossState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CChaseState();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CChaseState() override;
	/**
	 * @brief �ǐ�
	 * @param �{�X�̃|�C���^
	 */
	virtual void Chase(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
private:
	static const int PLAY_TACKLE_FLAME = 300; //�^�b�N�������s����܂ł̃t���[��
	int m_PlayTackleCnt; //�^�b�N���܂ł̌v���p
};

//=============================================
//�G�l�~�[�̃X�^�����
//=============================================
class CBossStanState :public CBossState
{
public:
	/**
	 * @brief �ŏ�
	 * @param �{�X�̃|�C���^
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief �Ō�ɌĂ΂��֐�
	 * @param �{�X�̃|�C���^
	 */
	void End(CBossEnemy* boss) override;
	/**
	 * @brief �X�^��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Stan(CBossEnemy* boss);
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
private:
	static const int STAN_FRAME = 180; //�X�^������
	int m_StanCnt; //�X�^���v���J�E���g
};

//=============================================
//�G�l�~�[�̜p�j���
//=============================================
class CWanderingState : public CBossState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CWanderingState();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CWanderingState() override;
	/**
	 * @brief �p�j
	 * @param �{�X�̃|�C���^
	 */
	virtual void Wandering(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
private:
	static const int TRANSITION_FRAME = 60;
	int m_TransitionCnt;		//�X�e�[�g���ڂ�ς��P�\�J�E���g
	bool m_bDamage;				//�_���[�W�H�������
	D3DXVECTOR3 m_TargetRot;	//�ړI�̕���
};

//=============================================
//�G�l�~�[�̍������
//=============================================
class CConfusionBossState : public CBossState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CConfusionBossState();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CConfusionBossState() override;
	/**
	 * @brief �ŏ�
	 * @param �{�X�̃|�C���^
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief ����
	 * @param �{�X�̃|�C���^
	 */
	virtual void Confusion(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
private:
	static constexpr float CORRECTION_VALUE = 70.0f; //���A�N�V������UI�𐶐�����ۂ�Y�̕␳�l
	static const D3DXVECTOR3 SIZE; //���A�N�V������UI�̃T�C�Y

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
	/**
	 * @brief �R���X�g���N�^
	 */
	CTackleState();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTackleState() override;
	/**
	 * @brief �ŏ�
	 * @param �{�X�̃|�C���^
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief �I��
	 * @param �{�X�̃|�C���^
	 */
	void End(CBossEnemy* boss) override;
	/**
	 * @brief �^�b�N��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Tackle(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
};

//=============================================
//�G�l�~�[�̃v���C���[��T�����
//=============================================
class CSearchState : public CBossState
{
public:
	/**
	 * @brief �ŏ�
	 * @param �{�X�̃|�C���^
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief �T��
	 * @param �{�X�̃|�C���^
	 */
	virtual void Search(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��
	 */
	virtual void DrawDebug()override;
private:
	D3DXVECTOR3 m_TargetPos;
};

//=============================================
//�G�l�~�[�̖\�����
//=============================================
class CRampageState : public CBossState
{
public:
	/**
	 * @brief �ŏ�
	 * @param [in]�{�X�̃|�C���^
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief �I��
	 * @param [in]�{�X�̃|�C���^
	 */
	void End(CBossEnemy* boss) override;
	/**
	 * @brief �\��
	 * @param [in]�{�X�̃|�C���^
	 */
	virtual void Rampage(CBossEnemy* boss)override;
	/**
	 * @brief �f�o�b�O�\��/
	 */
	virtual void DrawDebug()override;
};
#endif