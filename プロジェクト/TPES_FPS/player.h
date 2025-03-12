//=============================================
//
//�v���C���[[player.h]
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

//=============================================
// �O���錾
//=============================================
class CPlayerState;
class CPlayerAvoidance;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;
class CBlink_UI;

//=============================================
//�v���C���[�N���X
//=============================================
class CPlayer:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int PLAYER_LIFE = 150; //�̗�
	static const int PLAYER_STAMINA = 100; //�X�^�~�i
	static const int AVOIDANCE_COST = 30; //����A�N�V�����̃X�^�~�i�R�X�g
	static const int PLAYER_PRIORITY = 8; //�`�揇

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	//�v���C���[�쐬
	static CPlayer* Create();

	void Damage(int nDamage); //�����蔻��

	void ResetRot(); //�����̃��Z�b�g

	void ColisionEnemy(); //�G�Ƃ̓����蔻��

	void ChangeDamageState(); //TODO�L�����N�^�[�ɂ܂Ƃ߂�

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //�v���C���[���͏���

	void ChangePlayerState(CPlayerState* state); //�v���C���[�̃X�e�[�g�؂�ւ�

	//���񂾉񐔐ݒ�
	inline void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	//�X�^�~�i�ݒ�
	inline void SetStamina(int Stamina)
	{
		m_Stamina = Stamina;
	}

	//�X���[�N���g���邩��ݒ�
	inline void SetIsSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	//������΂���Ă��邩�ݒ�
	inline void SetBlown(bool isBlown)
	{
		m_isBlown = isBlown;
	}

	//�u�����N�̎g����񐔐ݒ�
	inline void SetBlinkCnt(int BlinkCnt)
	{
		m_BlinkCnt = BlinkCnt;
	}

	//�G�l�~�[�Ƃ̓����蔻��ݒ�
	inline void SetEnemyColision(bool isColision)
	{
		m_isEnemyColision = isColision;
	}

	//���񂾉񐔎擾
	inline int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	//�X�^�~�i�擾
	inline int& GetStamina()
	{
		return m_Stamina;
	}

	//�u�����N���g����񐔎擾
	inline int& GetBlinkCnt()
	{
		return m_BlinkCnt;
	}

	//�X���[�N���g���邩�擾
	inline bool& GetIsSmoke()
	{
		return m_isSmoke;
	}

	//������΂���Ă��邩�擾
	inline bool& GetBlown()
	{
		return m_isBlown;
	}

	//�G�l�~�[�Ƃ̓����蔻��擾
	inline bool& GetEnemyColision()
	{
		return m_isEnemyColision;
	}

	CReticle* m_Raticle;	//���e�B�N���|�C���^

	CUlt* m_pUlt;			//�E���g�|�C���^

	CPlayerState* m_pPlayerState;	//�v���C���[�̏��

	CPlayerAvoidance* m_pAvoidance;	//����s��
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //�X�|�[���ʒu
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //�X�|�[������

	static const int IGNORE_COLLISION_FRAME = 150; //�����蔻�薳���t���[��
	static const int SMOKE_RECAST_FRAME = 900; //�X���[�N�����t���[��
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //�f�t�H���g�̃A�T���g�̃����[�h�t���[����
	static const int STAN_FRAME = 120; //�X�^���t���[����
	static const int DEFAULT_AR_DAMAGE = 10; //�f�t�H���g�̃A�T���g�̃_���[�W
	static const int STAMINA_RECOVERY = 1; //�X�^�~�i�񕜐��l
	static const int STAMINA_RECOVERY_FRAME = 5; //�X�^�~�i��STAMINA_RECOVERY���񕜂���܂ł̃t���[����
	static const int DAMAGE_FRAME = 30; //�_���[�W�t���[��

	static constexpr float DEADZONE_Y = -100.0f; //������߂�����v���C���[�j��
	static constexpr float RETICLE_CORRECTION_VALUE = 16.0f; //���e�B�N����Y���W�␳
	static constexpr float SMOKE_CORRECTION_VALUE = 50.0f; //�X���[�N���ˏo����ۂ̕␳�l
	static constexpr float SMOKE_SHOT_SPEED = 20.0f; //�X���[�N���ˏo����X�s�[�h

	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y
	static const D3DXVECTOR3 STAMINA_GAUGE_SIZE; //�X�^�~�i�̃T�C�Y
	static const D3DXVECTOR3 GUN_UI_POS;//�e��UI�̈ʒu
	static const D3DXVECTOR2 GUN_UI_SIZE;//�e��UI�̃T�C�Y

	void SetUI(); //UI�ݒ�
	void ReSpawn(); //���X�|�[��

	CAmmo_UI* m_pAmmoUI;	//�c�eUI

	CLife_UI* m_pLifeUI;	//�̗�UI

	CUlt_UI* m_pUltUI;		//�E���gUI

	CSmoke_UI* m_pSmokeUI;	//�X���[�NUI

	CBlink_UI* m_pBlinkUI;	//�u�����NUI

	CGunIcon* m_pGunIcon;	//�e�̃A�C�R��

	CHitCameraEffect* m_pHitCameraEffect;	//�q�b�g���̃J�����G�t�F�N�g

	void DebugPos();	//�f�o�b�O���ʒu���\��

	int m_IgnoreColisionCnt;	//�G�Ƃ̓����蔻�薳���J�E���g

	int m_SmokeRecastCnt;		//�X���[�N�̃N�[���^�C���J�E���g

	int m_DeathCnt; //���S��

	int m_Stamina; //�X�^�~�i

	int m_BlinkCnt; //�u�����N��

	int m_StaminaRecoveryCnt; //�X�^�~�i�񕜃J�E���g

	bool m_isEnemyColision; //�G�l�~�[�Ƃ̔�����Ƃ邩

	bool m_isRelorad; //�����[�h���邩�ǂ���

	bool m_isSmoke; //�X���[�N���g������

	bool m_isBlown; //�ӂ��Ƃ΂���Ă邩
};
#endif