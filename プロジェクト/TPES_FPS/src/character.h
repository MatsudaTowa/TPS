//=============================================
//
//�L�����N�^�[����[character.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
#include "model_parts.h"
#include "bullet.h"
#include "gun.h"
#include "character_behavior.h"
#include "character_state.h"
#include "wall.h"
#include "block.h"
#include "shadow.h"

//=============================================
//�O���錾
//=============================================
class CMove;
class CGunAttack;
class CStan;
class CConfusion;
class CCharacterState;

//=============================================
//�L�����N�^�[�N���X
//=============================================
class CCharacter : public CObjectX
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int CHARACTER_PRIORITY = 8;
	static const int MAX_MOTION = 100;
	static const int MAX_PARTS = 64; //�ő�p�[�c��
	static constexpr float  BOSS_FIELD_X = 600.0f; //�{�X���X���W

	struct RayHitInfo
	{
		float distance;
		BOOL hit;
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X���ɓ������Ă���
		bool bColision_Y; //Y���ɓ������Ă���
		bool bColision_Z; //Z���ɓ������Ă���
		float radius;
	};

	enum CHARACTER_STATE
	{
		CHARACTER_NORMAL = 0, //�ʏ���
		CHARACTER_DAMAGE, //�_���[�W���
		CHARACTER_STATE_MAX,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CCharacter(int nPriority = CHARACTER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CCharacter()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
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
	 * @brief ���[�V�����`��
	 */
	void MotionDraw();

	/**
	 * @brief �p�[�c�ǂݍ���
	 * @param [in]�t�@�C���̖��O
	 */
	void Load_Parts(const char* FileName);
	/**
	 * @brief ���[�V��������
	 * @param [in]�p�[�c��
	 */
	void Motion(int NumParts);
	/**
	 * @brief ���[�V�����ݒ�
	 * @param [in]�ǂ̃��[�V������
	 */
	void SetMotion(int Motion);
	/**
	 * @brief �d�͏���
	 */
	void Gravity();
	/**
	 * @brief �W�����v����
	 */
	void Jump();
	/**
	 * @brief �u���b�N�Ƃ̔���
	 * @param [in]�p�[�c��
	 */
	virtual void HitBlock(int NumParts);
	/**
	 * @brief ���Ƃ̔���
	 */
	void HitField(); 
	/**
	 * @brief �X���[�N�ƃ��C�̔���
	 * @param [in]����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @return �q�b�g���
	 */
	RayHitInfo PerformRaycast_Smoke(D3DXVECTOR3 vector, CCharacter* character);
	/**
	 * @brief �u���b�N�ƃ��C�̔���
	 * @param [in]����
	 * @param [in]�L�����N�^�[�|�C���^
	 * @return �q�b�g���
	 */
	RayHitInfo PerformRaycast_Block(D3DXVECTOR3 vector, CCharacter* character);
	/**
	 * @brief ���[���h�}�g���b�N�X�ϊ�
	 */
	void ConversionMtxWorld();

	/**
	 * @brief �_���[�W�̃X�e�[�g�ύX
	 */
	void ChangeDamageState();

	/**
	 * @brief �ړ��ʐݒ�
	 * @param [in]�ړ���
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	/**
	 * @brief �ߋ��̈ʒu�ݒ�
	 * @param [in]�ߋ��̈ʒu
	 */
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	/**
	 * @brief ���n���Ă邩�ݒ�
	 * @param [in]���n���Ă��邩
	 */
	inline void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	/**
	 * @brief �̗͐ݒ�
	 * @param [in]�̗�
	 */
	inline void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	/**
	 * @brief �X�e�[�g�ݒ�
	 * @param [in]�X�e�[�g�|�C���^
	 */
	inline void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	/**
	 * @brief �X�^���t���[�����ݒ�
	 * @param [in]�X�^���t���[��
	 */
	inline void SetStanFrame(int StanFrame)
	{
		m_StanFrame = StanFrame;
	}

	/**
	 * @brief �X�e�[�g�̃J�E���g�ݒ�
	 * @param [in]�X�e�[�g�J�E���g
	 */
	inline void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	/**
	 * @brief �X�e�[�g�̃t���[���ݒ�
	 * @param [in]�X�e�[�g�t���[��
	 */
	inline void SetStateFrame(int nStateFrame)
	{
		m_nStateFrame = nStateFrame;
	}

	/**
	 * @brief �W�����v���ݒ�
	 * @param [in]�W�����v��
	 */
	inline void SetJumpCnt(int nJumpCnt)
	{
		m_nJumpCnt = nJumpCnt;
	}

	/**
	 * @brief ���[�V�������I��������ݒ�
	 * @param [in]���[�V�����I���t���O
	 */
	inline void SetFinish(bool bFinish)
	{
		m_bLoopFinish = bFinish;
	}

	/**
	 * @brief �e�̃T�C�Y�ݒ�
	 * @param [in]�e�̃T�C�Y
	 */
	inline void SetShadowSize(D3DXVECTOR3 shadow_size)
	{
		m_ShadowSize = shadow_size;
	}

	/**
	 * @brief �e�̐ݒ�
	 * @param [in]�e�̃|�C���^
	 */
	inline void SetGun(CGun* gun)
	{
		m_pGun = gun;
	}

	/**
	 * @brief �ړ��̃X�g���e�W�[�ݒ�
	 * @param [in]�ړ��̃X�g���e�W�[�|�C���^
	 */
	inline void SetMoveStrategy(CMove* move)
	{
		m_pMove = move;
	}

	/**
	 * @brief �X�^���̃X�g���e�W�[�ݒ�
	 * @param [in]�X�^���X�g���e�W�[�|�C���^
	 */
	inline void SetStan(CStan* stan)
	{
		m_pStan = stan;
	}

	/**
	 * @brief �����̃X�g���e�W�[�ݒ�
	 * @param [in]�����̃X�g���e�W�[
	 */
	inline void SetConfusion(CConfusion* confusion)
	{
		m_pConfusion = confusion;
	}

	/**
	 * @brief �e�̍U���̃X�g���e�W�[�ݒ�
	 * @param [in]�e�̍U���̃X�g���e�W�[�|�C���^
	 */
	inline void SetGunAttack(CGunAttack* gun_attack)
	{
		m_pGunAttack =  gun_attack;
	}

	/**
	 * @brief �ړ��ʎ擾
	 * @return �ړ���
	 */
	inline D3DXVECTOR3& GetMove()
	{
		return m_move;
	}

	/**
	 * @brief �ߋ��̈ʒu�擾
	 * @return �ߋ��̈ʒu
	 */
	inline D3DXVECTOR3& GetOldPos()
	{
		return m_oldpos;
	}

	/**
	 * @brief �e�̃T�C�Y�擾
	 * @return �e�̃T�C�Y
	 */
	inline D3DXVECTOR3& GetShadowSize()
	{
		return m_ShadowSize;
	}

	/**
	 * @brief ���n���Ă邩�擾
	 * @return ���n���Ă邩
	 */
	inline bool& GetLaunding()
	{
		return m_bLanding;
	}

	/**
	 * @brief ���[�V�����I�����Ă邩�擾
	 * @return ���[�V�����I���t���O
	 */
	inline bool& GetFinish()
	{
		return m_bLoopFinish;
	}

	/**
	 * @brief �̗͎擾
	 * @return �̗�
	 */
	inline int& GetLife()
	{
		return m_nLife;
	}

	/**
	 * @brief �p�[�c���擾
	 * @return �p�[�c��
	 */
	inline int& GetNumParts()
	{
		return m_PartsCnt;
	}
	/**
	 * @brief �X�s�[�h�擾
	 * @return �X�s�[�h
	 */
	inline float& GetSpeed()
	{
		return m_Speed;
	}

	/**
	 * @brief �X�e�[�g�擾
	 * @return �X�e�[�g
	 */
	inline CHARACTER_STATE& GetState()
	{
		return m_State;
	}

	/**
	 * @brief �X�e�[�g�ύX�J�E���g�擾
	 * @return �X�e�[�g�ύX�J�E���g
	 */
	inline int& GetStateCnt()
	{
		return m_nStateCnt;
	}

	/**
	 * @brief �X�e�[�g�ύX�t���[���擾
	 * @return �X�e�[�g�ύX�t���[��
	 */
	inline int& GetStateFrame()
	{
		return m_nStateFrame;
	}

	/**
	 * @brief �W�����v���擾
	 * @return �W�����v��
	 */
	inline int& GetJumpCnt()
	{
		return m_nJumpCnt;
	}

	/**
	 * @brief �X�^���t���[���擾
	 * @return �X�^���t���[��
	 */
	inline int& GetStanFrame()
	{
		return m_StanFrame;
	}

	/**
	 * @brief �X�e�[�g�ύX
	 * @param [in]�X�e�[�g
	 */
	void ChangeState(CCharacterState* state);

	/**
	 * @brief �e�̎擾
	 * @return �e�̃|�C���^
	 */
	inline CGun* GetGun()
	{
		return m_pGun;
	}

	/**
	 * @brief �ړ��X�g���e�W�[�̎擾
	 * @return �ړ��̃X�g���e�W�[�|�C���^
	 */
	inline CMove* GetMoveStrategy()
	{
		return m_pMove;
	}

	/**
	 * @brief �X�^���X�g���e�W�[�擾
	 * @return �X�^���X�g���e�W�[�|�C���^
	 */
	inline CStan* GetStan()
	{
		return m_pStan;
	}

	/**
	 * @brief �����X�g���e�W�[�擾
	 * @return �����X�g���e�W�[�|�C���^
	 */
	inline CConfusion* GetConfusion()
	{
		return m_pConfusion;
	}

	/**
	 * @brief �e�̍U���X�g���e�W�[�擾
	 * @return �e�̍U���X�g���e�W�[�|�C���^
	 */
	inline CGunAttack* GetGunAttack()
	{
		return m_pGunAttack;
	}

	//�L�����N�^�[�̃X�e�[�g�p�^�[��
	CCharacterState* m_pCharacterState;

	//�p�[�c
	CModel_Parts* m_apModel[MAX_PARTS];

private:

	static constexpr float GRAVITY_MOVE = 2.0f; //�d�͒l
	static constexpr float GRAVITY_MAX = 100.0f; //�d�͍ő�l
	static constexpr float SHADOW_POS_Y = 0.5f; //�e��Y���W(�n�ʂ��班��������)
	static constexpr float MOVE_FRICTION = 0.3f; //�ړ���R
	static constexpr float COLLISION_SLACK = 20.0f; //�ǂƂ̔���̂�Ƃ�
	static constexpr float RAY_CORRECTION_VALUE = 20.0f; //���C���΂�Y�̕␳�l

	/**
	 * @brief �u���b�N��X���̔���
	 * @param [in]�p�[�c�ԍ�
	 * @param [in]�ʒu
	 * @param [in]�ŏ����W
	 * @param [in]�ő���W
	 * @param [in]�u���b�N�|�C���^
	 */
	void ColisionBlock_X(int PartsIdx,D3DXVECTOR3 CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	/**
	 * @brief �u���b�N��Y���̔���
	 * @param [in]�p�[�c�ԍ�
	 * @param [in][out]�ʒu
	 * @param [in]�ŏ����W
	 * @param [in]�ő���W
	 * @param [in]�u���b�N�|�C���^
	 */
	void ColisionBlock_Y(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	/**
	 * @brief �u���b�N��Z���̔���
	 * @param [in]�p�[�c�ԍ�
	 * @param [in][out]�ʒu
	 * @param [in]�ŏ����W
	 * @param [in]�ő���W
	 * @param [in]�u���b�N�|�C���^
	 */
	void ColisionBlock_Z(int PartsIdx,D3DXVECTOR3 CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	D3DXVECTOR3 m_move; //���x
	D3DXVECTOR3 m_oldpos; //�ߋ��̈ʒu
	bool m_bLanding; //���n���Ă邩�ǂ���
	bool m_bLoopFinish; //���[�v���[�V�������I�������
	int m_nLife; //�̗�
	int m_nShotBullet; //�������e��
	int m_nStateCnt; //�X�e�[�g�؂�ւ��v���J�E���g
	int m_nStateFrame; //�X�e�[�g�؂�ւ��v���t���[����
	int m_PartsCnt; //�p�[�c��
	int m_nMotionFrameCnt; //�؂�ւ��t���[���J�E���g
	int m_nKeySetCnt; //�L�[�؂�ւ��J�E���g
	int m_nJumpCnt; //�W�����v�J�E���g
	int m_Motion; //���[�V����(�e�I�u�W�F�N�g����񋓂��󂯎��)
	int m_StanFrame; //�X�^���̃t���[����
	float m_Speed; //�X�s�[�h
	float m_Jump; //�W�����v
	CHARACTER_STATE m_State; //�v���C���[���
	D3DXCOLOR m_col; //�J���[
	D3DXVECTOR3 m_ShadowSize; //�e�̃T�C�Y

	CShadow* m_pShadow; //�e

	//�L�[���\����
	struct Key
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 Trot;
	};

	//�L�[�ݒ�\����
	struct KeySet
	{
		int nFrame; //�t���[����
		Key key[MAX_KEY];
	};

	//���[�V�����ݒ�\����
	struct MotionSet
	{
		int nLoop; //���[�v���邩�ǂ���
		int nNumKey; //�L�[��
		KeySet keySet[MAX_PARTS];
	};

	struct MotionData
	{
		MotionSet motion_set[MAX_MOTION]; //���[�V�����ݒ�
		int parts;
		int idx[MAX_PARTS];
		int parent[MAX_PARTS];
		float speed;
		float jump;
		char path[MAX_PARTS][MAX_TXT];
		D3DXVECTOR3 parts_pos[MAX_PARTS];
		D3DXVECTOR3 parts_rot[MAX_PARTS];
	};
	MotionData m_motion_data;
	//�e
	CGun* m_pGun;

	CMove* m_pMove;

	CStan* m_pStan;

	CConfusion* m_pConfusion;

	CGunAttack* m_pGunAttack;
};
#endif