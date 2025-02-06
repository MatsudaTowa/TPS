//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"
#include "wave_boss.h"
#include "player.h"
#include "boss_enemy.h"
#include "block.h"
#include "object.h"
#include "smoke_range.h"
#include "block_piece.h"

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

			switch (boss->GetAxis())
			{
			case CBossEnemy::X:
				PickNextMovePoint(pMovePoint);
				break;
			case CBossEnemy::Z:
				PickNextMovePoint(pMovePoint);
				break;
			default:
				break;
			}

			boss->SetMotion(CBossEnemy::MOTION_MOVE);
		}
		else
		{//���B���Ă�����
			m_isMove = false;

			D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
			boss->SetMove(move);

			//���̈ړ���̒��I
			PickNextMovePoint(pMovePoint);

			boss->SetMotion(CBossEnemy::MOTION_NEUTRAL);

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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossChase::CBossChase():m_bTargetPlayer(true)
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
	CPlayer* pplayer = dynamic_cast<CPlayer*>(obj);

	//�v���C���[�̈ʒu�ւ̕������
	D3DXVECTOR3 Vector = pplayer->GetPos() - boss->GetPos();
	// �ړI�n�Ƃ̋������v�Z
	float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

	// ���B����p��臒l
	const float threshold = 200.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ��� ���������킾����߂Â������Ȃ��悤�ɒ���

	//�v���C���[�Ɍ������ē�����
	MovetoPlayer(distance, threshold, Vector, boss);

	D3DXVec3Normalize(&Vector, &Vector);

	// ���C�L���X�g�����s���A��Q�������邩����
	if (boss->PerformRaycast_Smoke(Vector, boss).hit)
	{
		m_bTargetPlayer = false;

		boss->ChangeState(new CConfusionBossState);
	}
	else if (boss->PerformRaycast_Block(Vector, boss).hit
		&&boss->PerformRaycast_Player(Vector, boss).distance > boss->PerformRaycast_Block(Vector, boss).distance)
	{
		m_bTargetPlayer = false;
		boss->ChangeState(new CSearchState);
	}
	else
	{
		m_bTargetPlayer = true;
	}
}

//=============================================
//�v���C���[�Ɍ������ē�����
//=============================================
void CBossChase::MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss)
{
	//�Ώە��Ƃ̊p�x�v�Z
	float angle = atan2f(Vector.x, Vector.z);
	// �܂��ړI�n�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ��������s��
	if (distance > threshold)
	{
		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(angle) * boss->GetSpeed();
		move.z += cosf(angle) * boss->GetSpeed();
		//�ړ��ʑ��
		boss->SetMove(move);
	}
	else
	{
		D3DXVECTOR3 move = {0.0f,0.0f,0.0f};
		//�ړ��ʑ��
		boss->SetMove(move);
	}

	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = boss->GetRot();
	rot.y = angle + D3DX_PI;
	//rot����
	boss->SetRot(rot);
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
		sprintf(&aStr[0], "\n\n\n\n�Ώ�:�v���C���[�ȊO");
	}
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossConfusion::CBossConfusion(): m_isRight(false), m_TurnCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossConfusion::~CBossConfusion()
{
}

//=============================================
//�������
//=============================================
void CBossConfusion::Confusion(CBossEnemy* boss, float StartRot_y)
{
	//���݂̕������擾
	D3DXVECTOR3 rot = boss->GetRot();

	//�ړ��ʂ��Z�o
	float Rot_Answer_y = rot.y - StartRot_y;
	
	//�����ړ�����
	MoveRot(rot, Rot_Answer_y, boss);

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf(boss->GetRot().y + D3DX_PI), 0.0f, cosf(boss->GetRot().y + D3DX_PI)};

	D3DXVec3Normalize(&vec, &vec);

	CCharacter::RayHitInfo HitPlayerInfo = PerformRaycast_Player(vec, boss);
	CCharacter::RayHitInfo HitBlockInfo = boss->PerformRaycast_Block(vec, boss);
	CCharacter::RayHitInfo HitSmokeInfo = boss->PerformRaycast_Smoke(vec, boss);

	if (HitPlayerInfo.hit && HitPlayerInfo.distance < HitBlockInfo.distance)
	{//��������
		//boss->ChangeState(new CChaseState);
	}
	if (m_TurnCnt >= NUM_TURN)
	{//����ɒB������
		m_TurnCnt = 0;
		boss->ChangeState(new CWanderingState);
	}
}

//=============================================
//�����𓮂����Č��n������
//=============================================
void CBossConfusion::MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CBossEnemy* boss)
{
	if (m_isRight)
	{
		rot.y += 0.01f;

		if (Rot_Answer_y > LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = false;
			++m_TurnCnt;
		}
	}
	if (!m_isRight)
	{
		rot.y -= 0.01f;

		if (Rot_Answer_y < -LOOK_RANGE)
		{//�͈͂ɓ��B������t��]
			m_isRight = true;
			++m_TurnCnt;
		}
	}
	boss->SetRot(rot);
}

//=============================================
//�v���C���[�ƃ��C��������̂��`�F�b�N
//=============================================
CCharacter::RayHitInfo CBossConfusion::PerformRaycast_Player(D3DXVECTOR3 vector, CBossEnemy* boss)
{
	CCharacter::RayHitInfo Info; //�q�b�g����Ԃ��ϐ�

	//������
	Info.distance = -1.0f; //��Βl�ŕԂ�̂œ�����Ȃ��������p��-����
	Info.hit = false; //�������Ă��Ȃ���Ԃ�

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
		 //�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				//���C�����_����̍��������΂�(y�̓G�l�~�[�����΂��ۂ̍�������)
				D3DXVECTOR3 StartRay = {boss->GetPos().x - pPlayer->GetPos().x,boss->GetPos().y + 20.0f,boss->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer::NUM_PARTS; nCnt++)
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
//�e�U��
//=============================================
void CBossGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CBossEnemy::Motion_Type Motion;
	Motion = CBossEnemy::Motion_Type::MOTION_ATTACK;
	//���[�V�������
	character->SetMotion(Motion);
	if (character->m_pGun->GetAmmo() > 0)
	{
		if (character->m_pGunAttack != nullptr)
		{
			character->m_pGun->m_nRateCnt++;
			if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
			{
				character->m_pGun->m_nRateCnt = 0;
				D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI) * 45.0f,
					character->m_apModel[14]->GetMtxWorld()._42 + 5.0f, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI) * 45.0f);

				D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
					0.0f, cosf(character->GetRot().y + D3DX_PI) * character->m_pGun->GetBulletSpeed());

				character->m_pGun->m_nRateCnt = 0;
				//�e����
				character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->GetDamage(), Allegiance, type, character->m_pGun);					
			}
		}
	}
	else
	{
		character->m_pGun->m_pReload->Reload(character->m_pGun);
	}
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossTackle::CBossTackle():m_StayCnt(0), m_TackleCnt(0), m_isTackle(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossTackle::~CBossTackle()
{
}

//=============================================
//�^�b�N���U��
//=============================================
void CBossTackle::Tackle(CBossEnemy* boss)
{
	//�����[�h
	boss->m_pGun->Reload();

	if (!m_isTackle)
	{//�^�b�N�����ĂȂ�������
		LookAtPlayer(boss);
		++m_StayCnt;
	}

	if (m_StayCnt > STAY_FLAME)
	{//�J�E���g������J�E���g�ɓ��B������
		//�^�b�N��SE��炷
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TACKLE);
		m_isTackle = true;
		m_StayCnt = 0;
	}

	if (m_isTackle)
	{
		boss->SetMotion(CBossEnemy::MOTION_TACKLE);

		if (boss->m_pDashEffect == nullptr)
		{
			float fAngle = atan2f(sinf(boss->GetRot().y), cosf(boss->GetRot().y));

			//�_�b�V���G�t�F�N�g����
			boss->m_pDashEffect = CDashEffect::Create({boss->m_apModel[3]->GetMtxWorld()._41,boss->m_apModel[3]->GetMtxWorld()._42 - 100.0f,boss->m_apModel[3]->GetMtxWorld()._43 }
			, { 0.0f,fAngle,0.0f });
		}

		++m_TackleCnt;

		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(boss->GetRot().y) * boss->GetSpeed() * -15.0f;
		move.z += cosf(boss->GetRot().y) * boss->GetSpeed() * -15.0f;

		//�ړ��ʑ��
		boss->SetMove(move);

		if (boss->m_pDashEffect != nullptr)
		{//�G�t�F�N�g����������
			//�G�t�F�N�g�𓮂���
			boss->m_pDashEffect->SetPos({ boss->m_apModel[3]->GetMtxWorld()._41,boss->m_apModel[3]->GetMtxWorld()._42 - 100.0f,boss->m_apModel[3]->GetMtxWorld()._43 });
		}

		//�����̕������擾
		D3DXVECTOR3 vec = { sinf(boss->GetRot().y + D3DX_PI), 0.0f, cosf(boss->GetRot().y + D3DX_PI) };

		boss->ColisionPlayer();

		for (int nCnt = 0; nCnt < boss->GetNumParts(); nCnt++)
		{
			if (m_TackleCnt > TACKLE_FLAME)
			{//�����ɓ����邩�I���t���[���ɓ��B������
				m_TackleCnt = 0;
				m_StayCnt = 0;
				m_isTackle = false;

				if (boss->m_pDashEffect != nullptr)
				{//�G�t�F�N�g����������
					//�G�t�F�N�g�j��
					boss->m_pDashEffect->Uninit();
					boss->m_pDashEffect = nullptr;
				}
				boss->ChangeState(new CBossStanState);
			}

			if (boss->m_apModel[nCnt]->GetColisionBlockInfo().bColision_Z
				|| boss->m_apModel[nCnt]->GetColisionBlockInfo().bColision_X)
			{
				if (boss->m_apModel[nCnt]->GetColisionBlockInfo().pBlock != nullptr)
				{
					boss->m_apModel[nCnt]->GetColisionBlockInfo().pBlock->CreatePiece();
					boss->m_apModel[nCnt]->GetColisionBlockInfo().pBlock->Uninit();
					boss->m_apModel[nCnt]->GetColisionBlockInfo().pBlock = nullptr;

					//���ׂẴp�[�c�𓖂����ĂȂ������
					ColisionReset(boss);
				}


				if (boss->m_pDashEffect != nullptr)
				{//�G�t�F�N�g����������
					//�G�t�F�N�g�j��
					boss->m_pDashEffect->Uninit();
					boss->m_pDashEffect = nullptr;
				}

				//�^�b�N����񏉊���
				m_TackleCnt = 0;
				m_StayCnt = 0;
				m_isTackle = false;
				boss->ChangeState(new CBossStanState);
				break;
			}
		}
	}
}

//=============================================
//�������ĂȂ������
//=============================================
void CBossTackle::ColisionReset(CBossEnemy* boss)
{
	for (int nCntParts = 0; nCntParts < boss->GetNumParts(); nCntParts++)
	{
		boss->m_apModel[nCntParts]->GetColisionBlockInfo().bColision_X = false;
		boss->m_apModel[nCntParts]->GetColisionBlockInfo().bColision_Z = false;
	}
}

//=============================================
//�v���C���[�̂ق�����������
//=============================================
void CBossTackle::LookAtPlayer(CCharacter* character)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pplayer = dynamic_cast<CPlayer*>(pObj);

				//�v���C���[�Ƃ̋����Z�o
				D3DXVECTOR3 Distance = pplayer->GetPos() - character->GetPos();

				//�v���C���[�Ɍ�����p�x���Z�o
				float fAngle = atan2f(Distance.x, Distance.z);

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
CBossStan::CBossStan()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossStan::~CBossStan()
{
}

//=============================================
//�X�^������
//=============================================
void CBossStan::Stan(CBossEnemy* boss)
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossSearch::CBossSearch()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossSearch::~CBossSearch()
{
}

//=============================================
//�T������
//=============================================
void CBossSearch::Search(CBossEnemy* boss,D3DXVECTOR3 TargetPos)
{
	//�Ώۂ̈ʒu�ւ̕������
	D3DXVECTOR3 point = { TargetPos.x - boss->GetPos().x,0.0f,TargetPos.z - boss->GetPos().z };

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

		switch (boss->GetAxis())
		{
		case CBossEnemy::NONE:
			move.x += sinf(angle) * boss->GetSpeed();
			move.z += cosf(angle) * boss->GetSpeed();
			break;
		case CBossEnemy::X:
			boss->ChangeState(new CConfusionBossState);
			break;
		case CBossEnemy::Z:
			boss->ChangeState(new CConfusionBossState);
			break;
		default:
			break;
		}

		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = boss->GetRot();
		rot.y = angle + D3DX_PI;
		//rot����
		boss->SetRot(rot);
		//�ړ��ʑ��
		boss->SetMove(move);

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�k���|�C���^����Ȃ����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�G�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pplayer = dynamic_cast<CPlayer*>(pObj);
					//�v���C���[�̈ʒu�ւ̕������
					D3DXVECTOR3 Vector = pplayer->GetPos() - boss->GetPos();

					if (boss->PerformRaycast_Player(Vector, boss).hit
						&& boss->PerformRaycast_Block(Vector, boss).distance > boss->PerformRaycast_Player(Vector, boss).distance)
					{
						boss->ChangeState(new CChaseState);
					}
				}
			}
		}

		if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
		{
			boss->ChangeState(new CChaseState);
		}
	}
	else
	{//���B���Ă�����

		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
		boss->SetMove(move);

		boss->ChangeState(new CConfusionBossState);
	}
}
