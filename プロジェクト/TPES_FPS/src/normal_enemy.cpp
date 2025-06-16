//=============================================
//
//�ʏ�̓G�̏���[normal_enemy.cpp]
//Author Matsuda Towa
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
	if (GetMoveStrategy() == nullptr)
	{
		SetMoveStrategy(new CNormalMove);
	}
	if (GetGunAttack() == nullptr)
	{
		SetGunAttack(new CNormalAttack);
	}
	if (GetStan() == nullptr)
	{
		SetStan(new CEnemyStan);
	}
	if (GetConfusion() == nullptr)
	{
		SetConfusion(new CEnemyConfusion);
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
	if (GetGun() == nullptr)
	{
		SetGun(new CAssultRifle);
		GetGun()->Init();
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
	Motion(GetNumParts()); //���[�V��������
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
