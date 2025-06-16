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

/**
* @brief �����v���C���[�N���X
* @copydoc CPlayer
*/
class CActivePlayer :public CPlayer
{
public:
	static const int PLAYER_LIFE = 150; //�̗�
	static const int PLAYER_STAMINA = 100; //�X�^�~�i
	static const int AVOIDANCE_COST = 30; //����A�N�V�����̃X�^�~�i�R�X�g

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CActivePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CActivePlayer();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;

	/**
	 * @brief �_���[�W
	 */
	void Damage(int nDamage);
	/**
	 * @brief �����̃��Z�b�g
	 */
	void ResetRot();
	/**
	 * @brief �G�Ƃ̃q�b�g����
	 */
	void ColisionEnemy();

	/**
	 * @brief �G�̔���`�F�b�N
	 * @param [in]�G�̏��
	 * @param [in]�p�[�c�̐�
	 * @param [in]�ʒu���
	 * @param [in]�ŏ��̈ʒu
	 * @param [in]�ő�̈ʒu
	 */
	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3 pos, const D3DXVECTOR3 Minpos, const D3DXVECTOR3 Maxpos);
	/**
	 * @brief �v���C���[���͏���
	 */
	void Input();
	/**
	 * @brief �v���C���[�̃X�e�[�g�؂�ւ�
	 * @param [in]���̃X�e�[�g
	 */
	void ChangePlayerState(CPlayerState* state);

	/**
	 * @brief ���e�B�N���̐ݒ�
	 * @param [in]���e�B�N���|�C���^
	 */
	inline void SetReticle(CReticle* reticle)
	{
		m_Reticle = reticle;
	}

	/**
	 * @brief �E���g�̐ݒ�
	 * @param [in]�E���g�̃X�g���e�W�[�|�C���^
	 */
	inline void SetUlt(CUlt* ult)
	{
		m_pUlt = ult;
	}

	/**
	 * @brief ����̐ݒ�
	 * @param [in]����̃X�g���e�W�[�|�C���^
	 */
	inline void SetAvoidance(CPlayerAvoidance* avoidance)
	{
		m_pAvoidance = avoidance;
	}

	/**
	 * @brief ���S�񐔂̐ݒ�
	 * @param [in]���S��
	 */
	inline void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	/**
	 * @brief �X�^�~�i�̐ݒ�
	 * @param [in]�X�^�~�i�̒l
	 */
	inline void SetStamina(int Stamina)
	{
		m_Stamina = Stamina;
	}

	/**
	 * @brief �X���[�N���g���邩�̐ݒ�
	 * @param [in]�X���[�N���g���邩�ǂ���
	 */
	inline void SetIsSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	/**
	 * @brief ������΂���邩�̐ݒ�
	 * @param [in]������΂���Ă��邩�ǂ���
	 */
	inline void SetBlown(bool isBlown)
	{
		m_isBlown = isBlown;
	}

	/**
	 * @brief �u�����N�̃J�E���g�̐ݒ�
	 * @param [in]�u�����N�̃J�E���g
	 */
	inline void SetBlinkCnt(int BlinkCnt)
	{
		m_BlinkCnt = BlinkCnt;
	}

	/**
	 * @brief �G�l�~�[�Ɣ�����Ƃ邩�̐ݒ�
	 * @param [in]���肷�邩
	 */
	inline void SetEnemyColision(bool isColision)
	{
		m_isEnemyColision = isColision;
	}

	/**
	 * @brief ���e�B�N���̎擾
	 * @return ���e�B�N���|�C���^
	 */
	inline CReticle* GetReticle()
	{
		return m_Reticle;
	}

	/**
	 * @brief �E���g�̃X�g���e�W�[�̎擾
	 * @return �E���g�̃X�g���e�W�[�|�C���^
	 */
	inline CUlt* GetUlt()
	{
		return m_pUlt;
	}

	/**
	 * @brief ����̃X�g���e�W�[�̎擾
	 * @return ����̃X�g���e�W�[�|�C���^
	 */
	inline CPlayerAvoidance* GetAvoidance()
	{
		return m_pAvoidance;
	}

	/**
	 * @brief ���S�񐔂̎擾
	 * @return ���S��
	 */
	inline int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	/**
	 * @brief �X�^�~�i�̎擾
	 * @return �X�^�~�i��
	 */
	inline int& GetStamina()
	{
		return m_Stamina;
	}

	/**
	 * @brief �u�����N�̉񐔂̎擾
	 * @return �u�����N�̉�
	 */
	inline int& GetBlinkCnt()
	{
		return m_BlinkCnt;
	}

	/**
	 * @brief �X���[�N���g���邩�擾
	 * @return �X���[�N���g���邩�ǂ���
	 */
	inline bool& GetIsSmoke()
	{
		return m_isSmoke;
	}

	/**
	 * @brief ������΂���Ă邩�擾
	 * @return �X���[�N���g���邩�ǂ���
	 */
	inline bool& GetBlown()
	{
		return m_isBlown;
	}

	/**
	 * @brief �G�Ɣ������邩�擾
	 * @return �G�Ƃ̔������邩
	 */
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

	/**
	 * @brief �G�Ɣ���ǂ����邩(��������Ȃ瓖���蔻��A������Ȃ��Ȃ�J�E���g��i�߂�)
	 */
	void CanDetectEnemyCollision();

	/**
	 * @brief UI�𐶐�
	 */
	void CreateUI();

	/**
	 * @brief UI��ݒ�
	 */
	void SetUI();

	/**
	 * @brief ���X�|�[������
	 */
	void ReSpawn();

	/**
	 * @brief �f�o�b�O�\��
	 */
	void DebugPos();

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