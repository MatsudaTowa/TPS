//=============================================
//
//�{�X�̓G�̏���[boss_enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOSS_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"
#include "boss_behavior.h"
#include "boss_state.h"
#include"player.h"
#include "dash_effect.h"
#include "tackle_charge.h"

class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
class CBossSearch;
class CBossRampage;
class CBossState;

//�{�X�̃G�l�~�[�N���X
class CBossEnemy :public CEnemy
{
public:
	static const int NUM_PARTS = 15; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
	static const int PARTS_PARENT[NUM_PARTS]; //�p�[�c��
	static const int DEFAULT_LIFE = 1500; //���C�t
	static const int LOW_HP = DEFAULT_LIFE / 3; //�̗͂��Ⴂ
	static constexpr float FIND_PLAYER_DISTANCE = 300.0f; //���̒l�܂ł�������ǂ�������
	static constexpr float LOST_PLAYER_DISTANCE = 100.0f; //���̒l�ȏゾ�����猩����

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_TACKLE,
		MOTION_MAX,
	};

	CBossEnemy(int nPriority = ENEMY_PRIORITY);
	~CBossEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void ChangeState(CBossState* state);

	void TackleAction(); //�^�b�N���̎��s����

	void ColisionPlayer(); //�v���C���[�Ƃ̓����蔻��

	void CheckColisionPlayer(CPlayer* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;

	void HitBlock(int NumParts) override; //�u���b�N�����蔻��(�����p�[�c�p)

	void ColisionReset(); //�������ĂȂ������

	CBossChase* m_pChase; //�ǐՏ���

	CBossWandering* m_pWandering; //�p�j����

	CBossConfusion* m_pConfusion; //����

	CBossTackle* m_pTackle; //�^�b�N������

	CBossSearch* m_pSearch; //�T������

	CBossRampage* m_pRampage; //�\������

	CDashEffect* m_pTackleEffect; //�_�b�V���G�t�F�N�g

	CTackleCharge* m_pTackleCharge; //�^�b�N�����s���O�̃G�t�F�N�g

	//�������������̗�
	enum COLISION_AXIS
	{
		NONE,
		X,
		Z,
		MAX,
	};

	//�������������ݒ�
	inline void SethitAxis(COLISION_AXIS axis)
	{
		m_HitAxis = axis;
	}

	//�������������擾
	inline COLISION_AXIS& GetAxis()
	{
		return m_HitAxis;
	}
private:
	static constexpr float CORRECTION_VALUE_Y = 100.0f; //�^�b�N���G�t�F�N�g�𐶐�����ۂ�Y�̕␳�l

	static constexpr float TACKLE_VALUE = 15.0f; //�^�b�N�����̃X�s�[�h���Z

	static constexpr float PLAYER_KNOCKBACK_SPEED = 15.0f; //�^�b�N���������������Ƀm�b�N�o�b�N������ۂ�X��Z�ɂ�����X�s�[�h

	static constexpr float PLAYER_KNOCKBACK_Y = 30.0f; //�^�b�N���������������Ƀm�b�N�o�b�N������ۂ�Y�ɑł��グ��

	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�

	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y

	//�e�s������
	void CreateBossStrategy();

	//�e�s���j��
	void DeleteBossStrategy();

	//�X�e�[�g�̎��s����
	void ProcessState();

	//�f�o�b�O�\��
	void DrawDebug();

	Motion_Type m_Motion; //���[�V�����̎��

	CBossState* m_pBossState; //�{�X�̃X�e�[�g�p�^�[��

	COLISION_AXIS m_HitAxis; //�ǂ̕������瓖��������
};

#endif