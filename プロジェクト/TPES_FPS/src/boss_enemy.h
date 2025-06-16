//=============================================
//
//�{�X�̓G�̏���[boss_enemy.h]
//Author Matsuda Towa
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
#include "active_player.h"
#include "dash_effect.h"
#include "tackle_charge.h"

//=============================================
//�O���錾
//=============================================
class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
class CBossSearch;
class CBossRampage;
class CBossState;

//=============================================
//�{�X�̃G�l�~�[�N���X
//=============================================
class CBossEnemy :public CEnemy
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
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

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBossEnemy(int nPriority = ENEMY_PRIORITY);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CBossEnemy() override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
	/**
	 * @brief �X�V
	 */
	void Update() override;
	/**
	 * @brief �`��
	 */
	void Draw() override;
	/**
	 * @brief �X�e�[�g�ύX
	 * @param �{�X�̎��̃X�e�[�g
	 */
	void ChangeState(CBossState* state);
	/**
	 * @brief �^�b�N���̎��s����
	 */
	void TackleAction();
	/**
	 * @brief �v���C���[�Ƃ̔���
	 */
	void ColisionPlayer();
	/**
	 * @brief �v���C���[�Ƃ̃q�b�g����
	 * @param [in]�v���C���[�̃|�C���^
	 * @param [in]�p�[�c�̐�
	 * @param [in]�ʒu
	 * @param [in]�ő�̒��_���W
	 * @param [in]�ŏ��̒��_���W
	 */
	void CheckColisionPlayer(CActivePlayer* pPlayer, int nPartsCnt, const D3DXVECTOR3 pos, const D3DXVECTOR3 Minpos, const D3DXVECTOR3 Maxpos);
	/**
	 * @brief �E���g�q�b�g����
	 * @param [in]�E���g�̍��W
	 * @param [in]�_���[�W��
	 */
	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
	/**
	 * @brief �u���b�N�Ƃ̃q�b�g����(�����p�[�c)
	 * @param [in]�_���[�W��
	 */
	void HitBlock(int NumParts) override;
	/**
	 * @brief �������ĂȂ������
	 */
	void ColisionReset();

	/**
	 * @brief �ǐՂ̃|�C���^�擾
	 * @return �ǐՂ̃X�g���e�W�[�|�C���^
	 */
	CBossChase* GetBossChase()
	{
		return m_pChase;
	}

	/**
	 * @brief �p�j�̃|�C���^�擾
	 * @return �p�j�̃X�g���e�W�[�|�C���^
	 */
	CBossWandering* GetBossWandering()
	{
		return m_pWandering;
	}

	/**
	 * @brief �����̃|�C���^�擾
	 * @return �����̃X�g���e�W�[�|�C���^
	 */
	CBossConfusion* GetBossConfusion()
	{
		return m_pConfusion;
	}

	/**
	 * @brief �^�b�N���̃|�C���^�擾
	 * @return �^�b�N���̃X�g���e�W�[�|�C���^
	 */
	CBossTackle* GetBossTackle()
	{
		return m_pTackle;
	}

	/**
	 * @brief �T���̃|�C���^�擾
	 * @return �T���̃X�g���e�W�[�|�C���^
	 */
	CBossSearch* GetBossSearch()
	{
		return m_pSearch;
	}

	/**
	 * @brief �\���̃|�C���^�擾
	 * @return �\���̃X�g���e�W�[�|�C���^
	 */
	CBossRampage* GetBossRampage()
	{
		return m_pRampage;
	}

	/**
	 * @brief �_�b�V���G�t�F�N�g�擾
	 * @return �_�b�V���G�t�F�N�g�|�C���^
	 */
	CDashEffect* GetDashEffect()
	{
		return m_pTackleEffect;
	}

	/**
	 * @brief �^�b�N���`���[�W�G�t�F�N�g�擾
	 * @return �^�b�N���`���[�W�G�t�F�N�g�|�C���^
	 */
	CTackleCharge* GetTackleCharge()
	{
		return m_pTackleCharge;
	}

	/**
	 * @brief �_�b�V���G�t�F�N�g�ݒ�
	 * @param [in]�_�b�V���G�t�F�N�g�|�C���^
	 */
	void SetDashEffect(CDashEffect* effect)
	{
		m_pTackleEffect = effect;
	}

	/**
	 * @brief �^�b�N���`���[�W�G�t�F�N�g�ݒ�
	 * @param [in]�^�b�N���`���[�W�G�t�F�N�g�|�C���^
	 */
	void SetTackleCharge(CTackleCharge* charge)
	{
		m_pTackleCharge = charge;
	}

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

	/**
	 * @brief �e�s������
	 */
	void CreateBossStrategy();

	/**
	 * @brief �e�s���j��
	 */
	void DeleteBossStrategy();

	/**
	 * @brief �X�e�[�g���s
	 */
	void ProcessState();

	/**
	 * @brief �f�o�b�O�\��
	 */
	void DrawDebug();

	Motion_Type m_Motion; //���[�V�����̎��

	CBossState* m_pBossState; //�{�X�̃X�e�[�g�p�^�[��

	COLISION_AXIS m_HitAxis; //�ǂ̕������瓖��������

	CBossChase* m_pChase; //�ǐՏ���

	CBossWandering* m_pWandering; //�p�j����

	CBossConfusion* m_pConfusion; //����

	CBossTackle* m_pTackle; //�^�b�N������

	CBossSearch* m_pSearch; //�T������

	CBossRampage* m_pRampage; //�\������

	CDashEffect* m_pTackleEffect; //�_�b�V���G�t�F�N�g

	CTackleCharge* m_pTackleCharge; //�^�b�N�����s���O�̃G�t�F�N�g
};

#endif