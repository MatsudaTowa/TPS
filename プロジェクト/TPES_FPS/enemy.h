//=============================================
//
//�G�̏���[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "enemy_behavior.h"
#include "enemy_state.h"

class CEnemyState;

//�G�l�~�[�N���X
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

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void ChangeDamageState();
	void Draw() override;

	//�G�l�~�[�쐬
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type);

	void Damage(int nDamage); //�����蔻��

	virtual void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage); //�E���g�̔���

	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);

	static int m_NumEnemy; //�G�l�~�[�̑���
	ENEMY_TYPE m_Type; //�G�l�~�[�̎��
	int m_nCombatChangeCnt; //�퓬��Ԑ؂�ւ��J�E���g

private:
	//void ColisionUlt(D3DXVECTOR3& enemyPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);

	//�v���C���[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int NUM_MOTION; //���[�V�����̐�
	static const int STENCIL_FLAME; //�X�e���V���e�X�g�L��
	static constexpr int STAN_FRAME = 300; //�X�^������

	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void ReSpawn(); //���X�|�[��

	Motion_Type m_Motion; //���[�V�����̎��
	bool m_isStencil; //�X�e���V���e�X�g��L���ɂ��邩
	int m_StencilCnt; //�X�e���V���e�X�g�L���J�E���g
};

#endif