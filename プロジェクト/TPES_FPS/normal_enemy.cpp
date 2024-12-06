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
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CNormalAttack;
	}
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CEnemyConfusion;
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
