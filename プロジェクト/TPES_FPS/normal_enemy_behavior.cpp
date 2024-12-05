//=============================================
//
//�m�[�}���G�l�~�[�̃X�g���e�W�[�p�^�[��[normal_enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy_behavior.h"
#include "smoke_range.h"
#include "player_test.h"

//=============================================
//�R���X�g���N�^
//=============================================
CNormalMove::CNormalMove():m_nStateChangeCnt(0), m_nStayCnt(0), m_bRandom(), m_nLeft(), m_nRight()
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalMove::~CNormalMove()
{
}

//=============================================
//�ړ�
//=============================================
void CNormalMove::Move(CCharacter* character)
{
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		float move_x = 0.0f;

		if (m_bRandom)
		{
			move_x = 1.0f;
		}
		if (!m_bRandom)
		{
			move_x = -1.0f;
		}

		//���ɂ����ړ����Ȃ��̂�x�ɒl���
		SetMoveVec({ move_x,0.0f,0.0f });

		//�e�N���X�̈ړ����Ă�
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		Stay(character);
	}

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };
	CCharacter::RayHitInfo HitPlayerInfo = PerformRaycast_Player(vec, character);
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if ((HitPlayerInfo.hit
	&&HitPlayerInfo.distance < HitBlockInfo.distance)
	||character->GetState() == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��Ԃ������̓��C���v���C���[�ɓ������Ă�����
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);

		//�ˌ���Ԃ�
		character->ChangeState(new CShotState);
	}
}

//=============================================
//���C���v���C���[�ɓ������Ă�����
//=============================================
CCharacter::RayHitInfo CNormalMove::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info;

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
				D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y,character->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer_test::NUM_PARTS; nCnt++)
				{
					//���C���΂��v���C���[�Ɠ����邩�`�F�b�N
					D3DXIntersect(pPlayer->m_apModel[nCnt]->GetModelInfo(nCnt).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
					if (Info.hit == true)
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
//���ʂ����Ď~�܂�
//=============================================
void CNormalMove::Stay(CCharacter* character)
{
	character->SetRot({0.0f,0.0f,0.0f});

	if (m_nStayCnt < STAY_FRAME)
	{
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
		++m_nStayCnt;
	}
	if (m_nStayCnt >= STAY_FRAME)
	{
		m_nStateChangeCnt = 0;
		m_nStayCnt = 0;
		NextMove_X(character);
	}
}

//=============================================
//�����������I������玟�̕����𒊑I
//=============================================
void CNormalMove::NextMove_X(CCharacter* character)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, 100);

	//�ǂ����ɍs�����̊m��
	if (number(random) <= m_nRight)
	{
		m_bRandom = true;
		if (m_nRight > 0)
		{//�E�ɐi�ފm����������
			m_nRight -= 5;
		}
	}
	else if (number(random) > m_nRight && number(random) <= m_nLeft)
	{
		m_bRandom = false;
		if (m_nRight < 100)
		{//�E�ɐi�ފm����������
			m_nRight += 5;
		}
	}
}

//=============================================
//�R���X�g���N�^
//=============================================
CNormalAttack::CNormalAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalAttack::~CNormalAttack()
{
}

//=============================================
//�U��
//=============================================
void CNormalAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CEnemyGunAttack::GunAttack(Allegiance,type,character);

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	D3DXVec3Normalize(&vec, &vec);

	if (character->PerformRaycast_Smoke(vec, character).hit)
	{//�X���[�N�ɓ������Ă���
		character->ChangeState(new CConfusionState);
	}
}
