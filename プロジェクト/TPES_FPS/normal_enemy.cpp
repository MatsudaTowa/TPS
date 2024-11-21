//=============================================
//
//�ʏ�̓G�̏���[normal_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy.h"
#include "normal_enemy_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority)
{
	if (m_pMove == nullptr)
	{
		m_pMove = new CNormalMove;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CNormalAttack;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CNormalEnemy::Init()
{
	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	Load_Parts("data\\Motion.txt");
	SetLife(DEFAULT_LIFE);
	//�e�N���X�̏��������Ă�
	CEnemy::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CNormalEnemy::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CNormalEnemy::Update()
{
	CEnemy::Update();
	Motion(NUM_PARTS); //���[�V��������
}

//=============================================
//�`��
//=============================================
void CNormalEnemy::Draw()
{
	CEnemy::Draw();
}
