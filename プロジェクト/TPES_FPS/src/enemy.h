//=============================================
//
//�G�̏���[enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "enemy_behavior.h"

//=============================================
// �O���錾
//=============================================
class CEnemyState;

//=============================================
//�G�l�~�[�N���X
//=============================================
class CEnemy :public CCharacter
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
	static const int DEFAULT_LIFE = 5; //���C�t

	//�G�l�~�[�̗񋓒�`
	enum ENEMY_TYPE
	{
		ENEMY_TYPE_NORMAL = 0,
		ENEMY_TYPE_BOSS,
		ENEMY_TYPE_MAX,
	};

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CEnemy(int nPriority = ENEMY_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemy() override;
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
	 * @brief ����
	 * @param [in]�ʒu
	 * @param [in]����
	 * @param [in]�^�C�v
	 * @return �G�̃|�C���^
	 */
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type);

	/**
	 * @brief �_���[�W����
	 * @param [in]�_���[�W
	 */
	void Damage(int nDamage);

	/**
	 * @brief �E���g�̔���
	 * @param [in]�E���g�̈ʒu
	 * @param [in]�_���[�W
	 */
	virtual void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage);

	/**
	 * @brief �v���C���[�ƃ��C�̔���
	 * @param [in]����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @return ���C�q�b�g���
	 */
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);

	static int m_NumEnemy; //�G�l�~�[�̑���
private:
	static constexpr float DEFAULT_MOVE = 1.0f; //�ʏ펞�̈ړ�
	static constexpr float DAMPING_COEFFICIENT = 0.3f; //�ړ���R
	static const int DAMAGE_FRAME = 10; //�_���[�W�t���[��
	static constexpr float DEFAULT_JUMP = 25.0f; //�ʏ펞�̃W�����v��
	static constexpr float ULT_KNOCKBACK_SPEED = 10.0f; //ULT�������������Ƀm�b�N�o�b�N������ۂ�X��Z�ɂ�����X�s�[�h
	static constexpr float ULT_KNOCKBACK_Y = 40.0f; //ULT�������������Ƀm�b�N�o�b�N������ۂ�Y�ɑł��グ��
	static constexpr float DEADZONE_Y = -100.0f; //������߂�����G�l�~�[�j��
	static const int STENCIL_FLAME = 300; //�X�e���V���e�X�g�L��
	static const int STAN_FRAME = 300; //�X�^������
	static const int DEFAULT_SCORE = 300; //�f�t�H���g�̃X�R�A
	static const int BOSS_SCORE = 1000; //�{�X��|���������X�R�A

	/**
	 * @brief ���X�|�[��
	 */
	void ReSpawn();

	ENEMY_TYPE m_Type; //�G�l�~�[�̎��
	int m_nCombatChangeCnt; //�퓬��Ԑ؂�ւ��J�E���g

	Motion_Type m_Motion; //���[�V�����̎��
	bool m_isStencil; //�X�e���V���e�X�g��L���ɂ��邩
	int m_StencilCnt; //�X�e���V���e�X�g�L���J�E���g
};

#endif