//=============================================
//
//�ʏ�̓G�̏���[normal_enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _NORMAL_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"

//�ʏ�̃G�l�~�[�N���X
class CNormalEnemy :public CEnemy
{
public:
	static const int NUM_PARTS = 10; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
	static const int PARTS_PARENT[NUM_PARTS]; //�p�[�c��
	static const int DEFAULT_LIFE = 80; //���C�t

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	~CNormalEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
private:

	//�G�l�~�[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y
	static const int DEFAULT_AR_RELOAD_FRAME = 120; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int DEFAULT_AR_DAMAGE = 3; //�f�t�H���g�̃A�T���g�̃_���[�W

	Motion_Type m_Motion; //���[�V�����̎��
};

#endif