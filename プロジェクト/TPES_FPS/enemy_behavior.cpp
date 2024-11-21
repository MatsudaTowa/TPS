//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"
#include "manager.h"
#include "player_test.h"
#include "object.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyMove::CEnemyMove():m_move_vec({0.0f,0.0f,0.0f})
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
	//�ړ��̕����̒P�ʃx�N�g���ϐ�
	D3DXVECTOR3 vecDirection(m_move_vec);

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
}

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyAttack::CEnemyAttack()
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
	LookAtPlayer(character);
	//TODO:�e�̃I�t�Z�b�g����
	D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z);
	D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
	0.0f, cosf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed());

	if (character->m_pGun->GetAmmo() > 0)
	{
		character->m_pGun->m_nRateCnt++;
		if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
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
}

//=============================================
//�v���C���[�̂ق�����������
//=============================================
void CEnemyAttack::LookAtPlayer(CCharacter* character)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				//�v���C���[�Ƃ̋����Z�o
				D3DXVECTOR3 Distance = pPlayer_test->GetPos() - character->GetPos();

				//�v���C���[�Ɍ�����p�x���Z�o
				float fAngle = atan2f(Distance.x,Distance.z);

				//�e�N���X����rot���擾
				D3DXVECTOR3 rot = character->GetRot();

				rot.y = fAngle + D3DX_PI;

				character->SetRot(rot);
			}
		}
	}
}
