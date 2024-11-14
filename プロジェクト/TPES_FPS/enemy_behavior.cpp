//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyMove::CEnemyMove():m_nStateChangeCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyMove::~CEnemyMove()
{
}

//=============================================
//�ړ�����(�G�l�~�[)
//=============================================
void CEnemyMove::Move(CCharacter* character)
{
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		//�ړ��̕����̒P�ʃx�N�g���ϐ�
		D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		CEnemy::Motion_Type Motion;

		if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
		{ // �����ĂȂ��B
			Motion = CEnemy::Motion_Type::MOTION_NEUTRAL;
		}
		else
		{
			Motion = CEnemy::Motion_Type::MOTION_MOVE;
		}

		D3DXVECTOR3 move = character->GetMove();
		if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
		{ // �����ĂȂ��B
			move.x = 0.0f;
			move.z = 0.0f;
		}
		else
		{
			move.x += sinf(rotMoveY) * character->GetSpeed();
			move.z += cosf(rotMoveY) * character->GetSpeed();
		}
		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = character->GetRot();
		rot.y = rotMoveY + D3DX_PI;
		//rot����
		character->SetRot(rot);
		//�ړ��ʑ��
		character->SetMove(move);
		//���[�V�������
		character->SetMotion(Motion);
		++m_nStateChangeCnt;

	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		m_nStateChangeCnt = 0;
		//�ˌ���Ԃɐ؂�ւ�
		character->ChangeState(new CShotState);
	}
}

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyAttack::CEnemyAttack() :m_nStateChangeCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyAttack::~CEnemyAttack()
{
}

//=============================================
//�U������(�G�l�~�[)
//=============================================
void CEnemyAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	if (m_nStateChangeCnt < SHOT_FRAME)
	{
		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z);
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * CAssultRifle::DEFAULT_AR_BULLET_SPEED,
		0.0f, cosf(character->GetRot().y + D3DX_PI) * CAssultRifle::DEFAULT_AR_BULLET_SPEED);

		if (character->m_pGun->GetAmmo() > 0)
		{
			character->m_pGun->m_nRateCnt++;
			if (character->m_pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
			{
				character->m_pGun->m_nRateCnt = 0;
				//�e����
				character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->m_nDamage, Allegiance, type, character->m_pGun);
			}
		}
		else
		{
			character->m_pGun->m_pReload->Reload(character->m_pGun);
		}
		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= SHOT_FRAME)
	{
		m_nStateChangeCnt = 0;
		//�ړ���Ԃɐ؂�ւ�
		character->ChangeState(new CMoveState);
	}
}

//=============================================
//�e�̏���(�G�l�~�[)
//=============================================
void CEnemyAttack::GunAction(CGun* pGun, const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& size, int nDamage, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type)
{
	
}
