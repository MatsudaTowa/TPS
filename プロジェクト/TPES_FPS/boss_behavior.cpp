//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"
#include "wave_boss.h"
#include "player_test.h"
#include "boss_enemy.h"
#include "block.h"
#include "object.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBossWandering::CBossWandering():m_MoveIdx(0), m_StopCnt(0), m_isMove()
{
	m_isMove = true;
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossWandering::~CBossWandering()
{
}

//=============================================
//�p�j
//=============================================
void CBossWandering::Wandering(CBossEnemy* boss)
{
	if (m_isMove)
	{
		//�ړ���̏��擾(�������ړ���̃|�C���g�̔z��ԍ�)
		CMovePoint* pMovePoint = CWave_Boss::GetMovePoint(m_MoveIdx);

		//�Ώۂ̈ʒu�ւ̕������
		D3DXVECTOR3 point = { pMovePoint->GetPos().x - boss->GetPos().x,0.0f,pMovePoint->GetPos().z - boss->GetPos().z };

		// �ړI�n�Ƃ̋������v�Z
		float distance = sqrtf(point.x * point.x + point.z * point.z);

		// ���B����p��臒l
		const float threshold = 0.5f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j

		// �܂��ړI�n�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ��������s��
		if (distance > threshold)
		{
			//�Ώە��Ƃ̊p�x�v�Z
			float angle = atan2f(point.x, point.z);

			D3DXVECTOR3 move = boss->GetMove();

			move.x += sinf(angle) * boss->GetSpeed();
			move.z += cosf(angle) * boss->GetSpeed();
			//�e�N���X����rot���擾
			D3DXVECTOR3 rot = boss->GetRot();
			rot.y = angle + D3DX_PI;
			//rot����
			boss->SetRot(rot);
			//�ړ��ʑ��
			boss->SetMove(move);
		}
		else
		{//���B���Ă�����
			m_isMove = false;

			D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
			boss->SetMove(move);

			//���̈ړ���̒��I
			PickNextMovePoint(pMovePoint);
		}
	}
	else if (!m_isMove)
	{//�����Ȃ���ԂȂ�
		//�w��t���[�����~�܂�
		StopCnt();
	}
}

//=============================================
//�w��t���[�����~�܂�
//=============================================
void CBossWandering::StopCnt()
{
	++m_StopCnt;
	if (m_StopCnt > STOP_FRAME)
	{
		m_StopCnt = 0;
		m_isMove = true;
	}
}

//=============================================
//���̈ړ���̒��I
//=============================================
void CBossWandering::PickNextMovePoint(CMovePoint* pMovePoint)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, pMovePoint->GetNumPoint());
	//�����_���ňʒu�w��
  	m_MoveIdx = number(random);
	if (m_MoveIdx >= pMovePoint->GetNumPoint())
	{
		m_MoveIdx = 0;
	}
}

//=============================================
//�p�j�̃f�o�b�O�\��
//=============================================
void CBossWandering::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n[�{�X�i�ވʒu]%d"
		,m_MoveIdx );
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossChase::CBossChase():m_bTargetPlayer(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossChase::~CBossChase()
{
}

//=============================================
//�ǐ�
//=============================================
void CBossChase::Chase(CBossEnemy* boss, CObject* obj)
{
	CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(obj);

	//�v���C���[�̈ʒu�ւ̕������
	D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

	// �ړI�n�Ƃ̋������v�Z
	float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

	D3DXVec3Normalize(&Vector, &Vector);

	// ���B����p��臒l
	const float threshold = 200.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ��� ���������킾����߂Â������Ȃ��悤�ɒ���

	// ���C�L���X�g�����s���A��Q�������邩����
	m_bTargetPlayer = PerformRaycast(boss->GetPos(), Vector, boss->LOST_PLAYER_DISTANCE);

	if (m_bTargetPlayer)
	{
		//�v���C���[�Ɍ������ē�����
		MovetoPlayer(distance, threshold, Vector, boss);
	}
	else
	{
		boss->ChangeState(new CWanderingState);
	}
}

//=============================================
//�v���C���[�Ɍ������ē�����
//=============================================
void CBossChase::MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss)
{
	// �܂��ړI�n�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ��������s��
	if (distance > threshold)
	{
		//�Ώە��Ƃ̊p�x�v�Z
		float angle = atan2f(Vector.x, Vector.z);

		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(angle) * boss->GetSpeed();
		move.z += cosf(angle) * boss->GetSpeed();
		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = boss->GetRot();
		rot.y = angle + D3DX_PI;
		//rot����
		boss->SetRot(rot);
		//�ړ��ʑ��
		boss->SetMove(move);
	}
	else
	{
		D3DXVECTOR3 move = {0.0f,0.0f,0.0f};
		//�ړ��ʑ��
		boss->SetMove(move);
	}
}

//=============================================
//��Q�������邩����
//=============================================
bool CBossChase::PerformRaycast(const D3DXVECTOR3& startPos, const D3DXVECTOR3& direction, float maxDistance)
{
	// ���C�̏I�_���v�Z
	D3DXVECTOR3 endPos = startPos + direction * maxDistance;

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++) 
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
				// �o�E���f�B���O�{�b�N�X�擾
				D3DXVECTOR3 boxMin = pBlock->GetMinPos();
				D3DXVECTOR3 boxMax = pBlock->GetMaxPos();
				// �u���b�N�Ƃ̏Փ˔���
				if (CManager::GetInstance()->GetColision()->CheckIntersectRay(startPos, direction, boxMin, boxMax))
				{
					// ��Q�����Ԃɂ���ꍇ
					return false;
				}
			}
		}
	}
	// ��Q�����Ȃ��A�v���C���[�܂Ń��C�����B����ꍇ
	return true;
}

//=============================================
//�ǐՂ̃f�o�b�O�\��
//=============================================
void CBossChase::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	if (m_bTargetPlayer)
	{
		sprintf(&aStr[0], "\n\n\n\n�Ώ�:�v���C���[");
	}
	else if (!m_bTargetPlayer)
	{
		sprintf(&aStr[0], "\n\n\n\n�Ώ�:�u���b�N");
	}
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossGunAttack::CBossGunAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossGunAttack::~CBossGunAttack()
{
}

//=============================================
//�U��
//=============================================
void CBossGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CBossEnemy::Motion_Type Motion;
	Motion = CBossEnemy::Motion_Type::MOTION_ATTACK;
	//���[�V�������
	character->SetMotion(Motion);
	if (character->m_pGunAttack != nullptr)
	{
		character->m_pGun->m_nRateCnt++;
		if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
		{
			character->m_pGun->m_nRateCnt = 0;
			//�e���甭��
			D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41,
				character->m_apModel[14]->GetMtxWorld()._42, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI));

			D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
				0.0f, cosf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed());
			//�e����
			character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->m_nDamage, Allegiance, type, character->m_pGun);
		}
	}
}