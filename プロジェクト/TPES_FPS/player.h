//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _player_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _player_H_
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
#include "gauge.h"
#include "blink_UI.h"

class CPlayerState;
class CPlayerSliding;
class CPlayerAvoidance;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;
class CBlink_UI;

//�v���C���[�N���X
class CPlayer:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int PLAYER_LIFE = 150; //�̗�
	static const int PLAYER_STAMINA = 100; //�X�^�~�i
	static const int AVOIDANCE_COST = 30; //����A�N�V�����̃X�^�~�i�R�X�g
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
		MOTION_STAN,
		MOTION_MAX,
	}Motion_Type;

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	void ResetRot(); //�����̃��Z�b�g

	void ColisionEnemy(); //�G�Ƃ̓����蔻��

	void ChangeDamageState(); //TODO�L�����N�^�[�ɂ܂Ƃ߂�

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //�v���C���[���͏���

	void ChangePlayerState(CPlayerState* state);

	inline void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	inline void SetStamina(int Stamina)
	{
		m_Stamina = Stamina;
	}

	inline void SetSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	inline void SetBlown(bool isBlown)
	{
		m_isBlown = isBlown;
	}

	inline void SetBlinkCnt(int BlinkCnt)
	{
		m_BlinkCnt = BlinkCnt;
	}

	inline void SetEnemyColision(bool isColision)
	{
		m_isEnemyColision = isColision;
	}

	inline int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	inline int& GetStamina()
	{
		return m_Stamina;
	}

	inline int& GetBlinkCnt()
	{
		return m_BlinkCnt;
	}

	inline bool& GetSmoke()
	{
		return m_isSmoke;
	}

	inline bool& GetBlown()
	{
		return m_isBlown;
	}

	inline bool& GetEnemyColision()
	{
		return m_isEnemyColision;
	}
	CReticle* m_Raticle;

	CUlt* m_pUlt;

	CPlayerSliding* m_pSliding;

	CPlayerState* m_pPlayerState;

	CPlayerAvoidance* m_pAvoidance;
private:

	//�v���C���[�̈ړ��֘A
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const int MAX_JUMPCNT; //�W�����v��
	static const int IGNORE_COLLISION_FRAME; //�����蔻�薳���t���[��
	static const int SMOKE_RECAST_FRAME; //�X���[�N�����t���[��
	static const float DEADZONE_Y; //������߂�����v���C���[�j��
	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y
	static const D3DXVECTOR3 STAMINA_GAUGE_SIZE; //�X�^�~�i�̃T�C�Y
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int STAN_FRAME = 120; //�X�^���t���[����
	static const int DEFAULT_AR_DAMAGE = 10; //�f�t�H���g�̃A�T���g�̃_���[�W
	static const int STAMINA_RECOVERY = 1; //�X�^�~�i�񕜐��l
	static const int STAMINA_RECOVERY_FRAME = 5; //�X�^�~�i��STAMINA_RECOVERY���񕜂���܂ł̃t���[����

	void SetUI(); //UI�ݒ�
	void ReSpawn(); //���X�|�[��
	static CAmmo_UI* m_pAmmoUI;
	static CLife_UI* m_pLifeUI;

	CUlt_UI* m_pUltUI;
	CSmoke_UI* m_pSmokeUI;
	CBlink_UI* m_pBlinkUI;

	CGauge_3D* m_pStaminaGauge;

	CGunIcon* m_pGunIcon;

	CHitCameraEffect* m_pHitCameraEffect;

	void DebugPos();

	int m_IgnoreColisionCnt;

	int m_SmokeRecastCnt;

	int m_DeathCnt; //���S��

	int m_Stamina; //�X�^�~�i

	int m_BlinkCnt; //�u�����N��

	int m_StaminaRecoveryCnt; //�X�^�~�i�񕜃J�E���g

	bool m_isEnemyColision; //�G�l�~�[�Ƃ̔�����Ƃ邩

	bool m_isRelorad; //�����[�h���邩�ǂ���

	bool m_isSmoke; //�X���[�N���g������

	bool m_isBlown; //�X���[�N���g������
};
#endif