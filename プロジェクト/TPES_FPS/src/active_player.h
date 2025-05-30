//=============================================
//
//�������v���C���[(�`���[�g���A����Q�[���Ȃ�)[active_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ACTIVE_PLAYER_H_
#include "main.h"
#include "model_parts.h"
#include "player.h"
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
//�������v���C���[�N���X
//=============================================
class CActivePlayer :public CPlayer
{
public:
	static const int PLAYER_LIFE = 150; //�̗�
	static const int PLAYER_STAMINA = 100; //�X�^�~�i
	static const int AVOIDANCE_COST = 30; //����A�N�V�����̃X�^�~�i�R�X�g

	CActivePlayer(int nPriority = PLAYER_PRIORITY);
	~CActivePlayer();
	HRESULT Init();
	void CreateUI();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	void Damage(int nDamage); //�����蔻��

	void ResetRot(); //�����̃��Z�b�g

	void ColisionEnemy(); //�G�Ƃ̓����蔻��

	void ChangeDamageState(); //TODO�L�����N�^�[�ɂ܂Ƃ߂�

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //�v���C���[���͏���

	void ChangePlayerState(CPlayerState* state); //�v���C���[�̃X�e�[�g�؂�ւ�

	//���e�B�N���ݒ�
	inline void SetReticle(CReticle* reticle)
	{
		m_Reticle = reticle;
	}

	//�E���g�ݒ�
	inline void SetUlt(CUlt* ult)
	{
		m_pUlt = ult;
	}

	//���ݒ�
	inline void SetAvoidance(CPlayerAvoidance* avoidance)
	{
		m_pAvoidance = avoidance;
	}

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

	//���e�B�N���擾
	inline CReticle* GetReticle()
	{
		return m_Reticle;
	}
	//�E���g�擾
	inline CUlt* GetUlt()
	{
		return m_pUlt;
	}
	//����擾
	inline CPlayerAvoidance* GetAvoidance()
	{
		return m_pAvoidance;
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
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //�X�|�[���ʒu
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //�X�|�[������

	static const int IGNORE_COLLISION_FRAME = 150; //�����蔻�薳���t���[��
	static const int SMOKE_RECAST_FRAME = 900; //�X���[�N�����t���[��
	static const int STAN_FRAME = 120; //�X�^���t���[����
	static const int STAMINA_RECOVERY = 1; //�X�^�~�i�񕜐��l
	static const int STAMINA_RECOVERY_FRAME = 5; //�X�^�~�i��STAMINA_RECOVERY���񕜂���܂ł̃t���[����
	static const int DAMAGE_FRAME = 30; //�_���[�W�t���[��

	static constexpr float DEADZONE_Y = -100.0f; //������߂�����v���C���[�j��
	static constexpr float RETICLE_CORRECTION_VALUE = 16.0f; //���e�B�N����Y���W�␳
	static constexpr float SMOKE_CORRECTION_VALUE = 50.0f; //�X���[�N���ˏo����ۂ̕␳�l
	static constexpr float SMOKE_SHOT_SPEED = 20.0f; //�X���[�N���ˏo����X�s�[�h

	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y
	static const D3DXVECTOR3 GUN_UI_POS;//�e��UI�̈ʒu
	static const D3DXVECTOR2 GUN_UI_SIZE;//�e��UI�̃T�C�Y

	void SetUI();	//UI�ݒ�
	void ReSpawn(); //���X�|�[��
	void DebugPos();//�f�o�b�O���ʒu���\��

	CAmmo_UI* m_pAmmoUI;	//�c�eUI

	CLife_UI* m_pLifeUI;	//�̗�UI

	CUlt_UI* m_pUltUI;		//�E���gUI

	CSmoke_UI* m_pSmokeUI;	//�X���[�NUI

	CBlink_UI* m_pBlinkUI;	//�u�����NUI

	CGunIcon* m_pGunIcon;	//�e�̃A�C�R��

	CHitCameraEffect* m_pHitCameraEffect;	//�q�b�g���̃J�����G�t�F�N�g

	CPlayerState* m_pPlayerState;	//�v���C���[�̏��

	CReticle* m_Reticle;	//���e�B�N���|�C���^

	CUlt* m_pUlt;			//�E���g�|�C���^

	CPlayerAvoidance* m_pAvoidance;	//����s��

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