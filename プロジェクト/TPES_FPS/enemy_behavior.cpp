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
CEnemyGunAttack::CEnemyGunAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyGunAttack::~CEnemyGunAttack()
{
}

//=============================================
//�U������(�G�l�~�[)
//=============================================
void CEnemyGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
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

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	// ���C�L���X�g�����s���A��Q�������邩����TODO:��������u���b�N�͏��O
	if (character->PerformRaycast_Smoke(vec, character).hit)
	{
		character->ChangeState(new CConfusionState);
	}
}

//=============================================
//�v���C���[�̂ق�����������
//=============================================
void CEnemyGunAttack::LookAtPlayer(CCharacter* character)
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

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyConfusion::CEnemyConfusion() : m_isRight(false), m_TurnCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyConfusion::~CEnemyConfusion()
{
}

//=============================================
//����
//=============================================
void CEnemyConfusion::Confusion(CCharacter* character, float StartRot_y)
{
	//���݂̕������擾
	D3DXVECTOR3 rot = character->GetRot();

	//�ړ��ʂ��Z�o
	float Rot_Answer_y = rot.y - StartRot_y;

	//�����ړ�����
	MoveRot(rot, Rot_Answer_y, character);

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	D3DXVec3Normalize(&vec, &vec);

	CCharacter::RayHitInfo HitPlayerInfo = PerformRaycast_Player(vec, character);
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if (HitPlayerInfo.hit && HitPlayerInfo.distance < HitBlockInfo.distance)
	{//��������
		character->ChangeState(new CShotState);
	}
	if (m_TurnCnt >= NUM_TURN)
	{//����ɒB������
		m_TurnCnt = 0;
		character->ChangeState(new CMoveState);
	}
}

//=============================================
//�����ړ�
//=============================================
void CEnemyConfusion::MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character)
{
	if (m_isRight)
	{
		rot.y += 0.005f;

		if (Rot_Answer_y > LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = false;
			++m_TurnCnt;
		}
	}
	if (!m_isRight)
	{
		rot.y -= 0.005f;

		if (Rot_Answer_y < -LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = true;
			++m_TurnCnt;
		}
	}
	character->SetRot(rot);
}

//=============================================
//����
//=============================================
CCharacter::RayHitInfo CEnemyConfusion::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info; //�q�b�g����Ԃ��ϐ�

		//������
	Info.distance = -1.0f; //��Βl�ŕԂ�̂œ�����Ȃ��������p��-����
	Info.hit = false; //�������Ă��Ȃ���Ԃ�

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
				CPlayer_test* pPlayer = dynamic_cast<CPlayer_test*>(pObj);

				//���C�����_����̍��������΂�(y�̓G�l�~�[�����΂��ۂ̍�������)
				D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer_test::NUM_PARTS; nCnt++)
				{
					//���C���΂��v���C���[�Ɠ����邩�`�F�b�N
					D3DXIntersect(pPlayer->m_apModel[nCnt]->GetModelInfo(nCnt).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
					if (Info.hit)
					{
						return Info;
					}
				}
			}
		}
	}
	return Info;
}

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyStan::CEnemyStan()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyStan::~CEnemyStan()
{
}

//=============================================
//�X�^������
//=============================================
void CEnemyStan::Stan(CCharacter* character)
{
	character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
}
