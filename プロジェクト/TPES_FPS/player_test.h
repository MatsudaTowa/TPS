//=============================================
//
//3DTemplate[player_test.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_TEST_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_TEST_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "reticle.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "player_behavior.h"
#include "enemy.h"
#include "hit_camera_effect.h"
#include "gun_icon.h"
#include "player_state.h"
#include "ult.h"
#include "smoke_UI.h"

class CPlayerState;
class CPlayerSliding;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;

//�v���C���[�N���X
class CPlayer_test:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int PLAYER_LIFE = 100; //�̗�
	static const int PLAYER_PRIORITY = 8; //�`�揇
	static const int PARTS_PARENT[NUM_PARTS]; //�p�[�c��

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //�X�|�[���ʒu
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //�X�|�[������
	//���[�V�����̎�ނ̗�
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	}Motion_Type;

	CPlayer_test(int nPriority = PLAYER_PRIORITY);
	~CPlayer_test();
	HRESULT Init();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	//�v���C���[�쐬
	static CPlayer_test* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	void ResetRot(); //�����̃��Z�b�g

	void ColisionEnemy(); //�G�Ƃ̓����蔻��

	void ChangeDamageState(); //TODO�L�����N�^�[�ɂ܂Ƃ߂�

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //�v���C���[���͏���

	void ChangePlayerState(CPlayerState* state);

	void SetSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	bool& GetSmoke()
	{
		return m_isSmoke;
	}

	CReticle* m_Raticle;

	CUlt* m_pUlt;

	CPlayerSliding* m_pSliding;

	CPlayerState* m_pPlayerState;
private:

	//�v���C���[�̈ړ��֘A
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const int MAX_JUMPCNT; //�W�����v��
	static const int IGNORE_COLLISION_FRAME; //�����蔻�薳���t���[��
	static const int SMOKE_RECAST_FRAME; //�X���[�N�����t���[��
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void SetUI(); //UI�ݒ�
	void ReSpawn(); //���X�|�[��
	static CAmmo_UI* m_pAmmoUI;
	static CLife_UI* m_pLifeUI;

	CUlt_UI* m_pUltUI;
	CSmoke_UI* m_pSmokeUI;

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	CGunIcon* m_pGunIcon;

	CHitCameraEffect* m_pHitCameraEffect;

	void DebugPos();

	int m_IgnoreColisionCnt;

	int m_SmokeRecastCnt;

	bool m_isEnemyColision; //�G�l�~�[�Ƃ̔�����Ƃ邩

	bool m_isRelorad; //�����[�h���邩�ǂ���

	bool m_isSmoke; //�X���[�N���g������
};
#endif