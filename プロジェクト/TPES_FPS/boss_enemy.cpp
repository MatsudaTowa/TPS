//=============================================
//
//�{�X�̓G�̏���[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBossEnemy::CBossEnemy(int nPriority)
{
	if (m_pMove == nullptr)
	{
		m_pMove = new CBossWandering;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CBossAttack;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossEnemy::~CBossEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CBossEnemy::Init()
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
void CBossEnemy::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBossEnemy::Update()
{
	CEnemy::Update();
	Motion(NUM_PARTS); //���[�V��������
}

//=============================================
//�`��
//=============================================
void CBossEnemy::Draw()
{
	CEnemy::Draw();
}
