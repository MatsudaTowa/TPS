//=============================================
//
//�G�l�~�[�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"
#include "manager.h"
#include "player.h"
#include "object.h"
#include "normal_enemy.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyMove::CEnemyMove():m_move_vec(VEC3_RESET_ZERO)
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

	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // �����ĂȂ��B
		Motion = CEnemy::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CEnemy::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // �����ĂȂ��B
		move.x = FLOAT_ZERO;
		move.z = FLOAT_ZERO;
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
void CEnemyGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	CNormalEnemy::Motion_Type Motion;
	Motion = CNormalEnemy::Motion_Type::MOTION_ATTACK;
	//���[�V�������
	character->SetMotion(Motion);

	CGun* gun = character->GetGun();

	D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI)* 45.0f,
		character->m_apModel[14]->GetMtxWorld()._42 + 5.0f, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI) * 45.0f);

	D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * gun->GetBulletSpeed(),
		0.0f, cosf(character->GetRot().y + D3DX_PI) * gun->GetBulletSpeed());

	if (gun->GetAmmo() > INT_ZERO)
	{
		int nRateCnt = gun->GetRateCnt();

		++nRateCnt;
		if (nRateCnt >= gun->GetFireRate())
		{
			nRateCnt = INT_ZERO;
			//�e����
			gun->m_pShot->Shot(ShotPos, ShotMove, gun->GetSize(), gun->GetDamage(), Allegiance, gun);
		}

		gun->SetRateCnt(nRateCnt);
	}
	else
	{
		gun->m_pReload->Reload(gun);
	}

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), FLOAT_ZERO, cosf(character->GetRot().y + D3DX_PI) };

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
	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

			//�v���C���[��T��
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//�v���C���[�Ƃ̋����Z�o
		D3DXVECTOR3 Distance = pPlayer->GetPos() - character->GetPos();

		//�v���C���[�Ɍ�����p�x���Z�o
		float fAngle = atan2f(Distance.x,Distance.z);

		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = character->GetRot();

		rot.y = fAngle + D3DX_PI;

		character->SetRot(rot);
	}
}

//�T�C�Y
const D3DXVECTOR3 CEnemyConfusion::SIZE = { 20.0f,20.0f,0.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CEnemyConfusion::CEnemyConfusion() : m_isRight(false), m_TurnCnt(INT_ZERO), m_pReaction()
{	
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemyConfusion::~CEnemyConfusion()
{
	if (m_pReaction != nullptr)
	{
		m_pReaction->Uninit();
		m_pReaction = nullptr;
	}
}

//=============================================
//����
//=============================================
void CEnemyConfusion::Confusion(CCharacter* character, float StartRot_y)
{
	if (m_pReaction == nullptr)
	{
		m_pReaction = CEnemy_Reaction_UI::Create({ character->m_apModel[1]->GetMtxWorld()._41,
			character->m_apModel[1]->GetMtxWorld()._42 + CORRECTION_VALUE,
			character->m_apModel[1]->GetMtxWorld()._43 }, SIZE,  CEnemy_Reaction_UI::REACTION::REACTION_CONFUSION);
	}
	//���݂̕������擾
	D3DXVECTOR3 rot = character->GetRot();

	//�ړ��ʂ��Z�o
	float Rot_Answer_y = rot.y - StartRot_y;

	//�����ړ�����
	MoveRot(rot, Rot_Answer_y, character);

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), FLOAT_ZERO, cosf(character->GetRot().y + D3DX_PI) };

	D3DXVec3Normalize(&vec, &vec);

	CCharacter::RayHitInfo HitPlayerInfo;

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);
	
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if (HitPlayerInfo.hit && HitPlayerInfo.distance < HitBlockInfo.distance)
	{//��������
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		character->ChangeState(new CShotState);
		return;
	}
	if (character->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		character->ChangeState(new CStanState);
		return;
	}
	if (m_TurnCnt >= NUM_TURN)
	{//����ɒB������
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		m_TurnCnt = INT_ZERO;
		character->ChangeState(new CMoveState);
		return;
	}
}

//=============================================
//�����ړ�
//=============================================
void CEnemyConfusion::MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character)
{
	if (m_isRight)
	{
		rot.y += ROT_MOVE;

		if (Rot_Answer_y > LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = false;
			++m_TurnCnt;
		}
	}
	if (!m_isRight)
	{
		rot.y -= ROT_MOVE;

		if (Rot_Answer_y < -LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = true;
			++m_TurnCnt;
		}
	}
	character->SetRot(rot);
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
	character->SetMotion(CNormalEnemy::Motion_Type::MOTION_STAN);
}
