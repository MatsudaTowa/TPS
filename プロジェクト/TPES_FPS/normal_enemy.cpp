//=============================================
//
//�ʏ�̓G�̏���[normal_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy.h"
#include "normal_enemy_behavior.h"

//�e�̃T�C�Y
const D3DXVECTOR3 CNormalEnemy::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

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

		m_pGun->SetReloadFrame(DEFAULT_AR_RELOAD_FRAME);
		m_pGun->SetDamage(DEFAULT_AR_DAMAGE);

		m_pGun->Init();
	}

	SetLife(DEFAULT_LIFE);

	//�e�̃T�C�Y�ݒ�
	SetShadowSize(SHADOW_SIZE);

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

//=============================================
//�E���g�q�b�g����
//=============================================
void CNormalEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	ChangeState(new CStanState);

	//�e�N���X�̃q�b�g����
	CEnemy::MediumUltHit(UltPos,nDamage);
}
