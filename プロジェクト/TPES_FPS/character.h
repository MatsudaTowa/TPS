//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
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


//=============================================
//�O���錾
//=============================================
class CMove;
class CAttack;
class CCharacterState;

//�v���C���[�N���X
class CCharacter : public CObjectX
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int MAX_MOTION = 5;
	static const int MAX_PARTS = 12; //�ő�p�[�c��
	static const float  BOSS_FIELD_X; //�{�X���X���W

	typedef enum
	{
		CHARACTER_NORMAL = 0, //�ʏ���
		CHARACTER_DAMAGE, //�_���[�W���
		CHARACTER_STATE_MAX,
	}CHARACTER_STATE;

	CCharacter(int nPriority);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void MotionDraw(int NumParts);
	void MotionDraw(int NumParts,D3DXCOLOR col);

	void Load_Parts(const char* FileName);
	void Motion(int NumParts); //���[�V��������
	void SetMotion(int Motion); //�����Ŏw�肵�����[�V�����ɐ؂�ւ���
	void Gravity(); //�d�͏���
	void Jump(); //�W�����v����
	void HitBlock(); //�u���b�N�����蔻��
	void HitField(); //�������蔻��
	void HitWall(); //�Ǔ����蔻��

	//�ړ��ʑ��
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos���
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//���n���Ă邩�ǂ�������
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//�ǂ��������Ă邩�ǂ�������(true:�Efalse:��)
	void SetWay(bool bWay)
	{
		m_bWay = bWay;
	}

	//�̗͑��
	void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//��ԑ��
	void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	//�X�e�[�g�J�E���g���
	void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	//�W�����v�����
	void SetJumpCnt(int nJumpCnt)
	{
		m_nJumpCnt = nJumpCnt;
	}

	//�I����������
	void SetFinish(bool bFinish)
	{
		m_bLoopFinish = bFinish;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3& GetMove();

	//�ߋ��̈ʒu�擾
	D3DXVECTOR3& GetOldPos();

	//���n���Ă邩�ǂ����擾
	bool& GetLaunding();

	//�ǂ��������Ă邩�ǂ������擾(true:�Efalse:��)
	bool& GetWay();

	//�I����Ă邩�擾
	bool& GetFinish();

	//�̗͎擾
	int& GetLife();

	float& GetSpeed();

	//��Ԏ擾
	CHARACTER_STATE& GetState();

	//�X�e�[�g�J�E���g�擾
	int& GetStateCnt();

	//�W�����v�񐔎擾
	int& GetJumpCnt();

	void ChangeState(CCharacterState* state);

	//�p�[�c
	CModel_Parts* m_apModel[MAX_PARTS];

	//�e
	CGun* m_pGun;

	CMove*m_pMove;

	CAttack*m_pAttack;

	//�L�����N�^�[�̃X�e�[�g�p�^�[��
	CCharacterState* m_pCharacterState;
private:
	static const float GRAVITY_MOVE; //�d�͒l
	static const float GRAVITY_MAX; //�d�͍ő�l

	//�ǂ̔���
	void ColisionWall_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);
	void ColisionWall_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);

	D3DXVECTOR3 m_move; //���x
	D3DXVECTOR3 m_oldpos; //�ߋ��̈ʒu
	bool m_bLanding; //���n���Ă邩�ǂ���
	bool m_bWay; //�ǂ��������Ă邩(true:�Efalse:��)
	bool m_bLoopFinish; //���[�v���[�V�������I�������
	int m_nLife; //�̗�
	int m_nShotBullet; //�������e��
	int m_nStateCnt; //�X�e�[�g�؂�ւ��v���J�E���g
	int m_PartsCnt; //�p�[�c��
	int m_nMotionFrameCnt; //�؂�ւ��t���[���J�E���g
	int m_nKeySetCnt; //�L�[�؂�ւ��J�E���g
	int m_nJumpCnt; //�W�����v�J�E���g
	int m_Motion; //���[�V����(�e�I�u�W�F�N�g����񋓂��󂯎��)
	float m_Speed; //�X�s�[�h
	float m_Jump; //�W�����v
	CHARACTER_STATE m_State; //�v���C���[���
	D3DXCOLOR m_col; //�J���[

	//�L�[���\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;

		D3DXVECTOR3 Trot;
	}Key;

	//�L�[�ݒ�\����
	typedef struct
	{
		int nFrame; //�t���[����
		Key key[MAX_KEY];
	}KeySet;

	//���[�V�����ݒ�\����
	typedef struct
	{
		int nLoop; //���[�v���邩�ǂ���
		int nNumKey; //�L�[��
		KeySet keySet[MAX_PARTS];
	}MotionSet;

	MotionSet m_MotionSet[MAX_MOTION]; //���[�V�����ݒ�
};
#endif