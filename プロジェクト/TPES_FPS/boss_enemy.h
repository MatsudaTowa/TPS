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
#include"player_test.h"

class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
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
	static const int DEFAULT_LIFE = 100; //���C�t
	static const float FIND_PLAYER_DISTANCE; //���̒l�܂ł�������ǂ�������
	static const float LOST_PLAYER_DISTANCE; //���̒l�ȏゾ�����猩����

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	};

	CBossEnemy(int nPriority = ENEMY_PRIORITY);
	~CBossEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void ChangeState(CBossState* state);

	void ColisionPlayer(); //�v���C���[�Ƃ̓����蔻��

	void CheckColisionPlayer(CPlayer_test* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	CBossChase* m_pChase; //�ǐՏ���

	CBossWandering* m_pWandering; //�p�j����

	CBossConfusion* m_pConfusion; //����

	CBossTackle* m_pTackle; //�^�b�N������
private:
	//�G�l�~�[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�

	void DrawDebug();

	Motion_Type m_Motion; //���[�V�����̎��

	//�{�X�̃X�e�[�g�p�^�[��
	CBossState* m_pBossState;
};

#endif