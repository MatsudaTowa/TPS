//=============================================
//
//�L�����N�^�[����[character.cpp]
//Author Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "field.h"
#include "colision.h"
#include "smoke_range.h"

//=============================================
//�R���X�g���N�^
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority),
m_bLanding(false),												//���n���Ă��邩
m_move(VEC3_RESET_ZERO),										//�ړ���
m_nLife(INT_ZERO),												//�̗�
m_nStateCnt(INT_ZERO),											//�_���[�W�X�e�[�g���ێ�����J�E���g
m_oldpos(VEC3_RESET_ZERO),										//�ߋ��̈ʒu
m_State(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL),			 //���̏��
m_PartsCnt(INT_ZERO),											//�p�[�c��
m_nMotionFrameCnt(INT_ZERO),									//���[�V�����̃t���[����
m_nKeySetCnt(INT_ZERO),											//�L�[�̌�
m_Motion(INT_ZERO),												//���[�V�������
m_bLoopFinish(),												//���[�v���I�������
m_Speed(),														//�X�s�[�h
m_Jump(),														//�W�����v��
m_pGun(),														//�e�̃|�C���^
m_motion_data(),													//���[�V�����ݒ�
m_pMove(),														//�ړ����鏈��
m_pGunAttack(),													//�e�̍U��
m_pStan(),														//�X�^������
m_pConfusion(),													//��������
m_pCharacterState(),											//�L�����N�^�[�̃X�e�[�g�p�^�[���|�C���^
m_nJumpCnt(INT_ZERO),											//�W�����v��
m_pShadow(),													//�e�̃|�C���^
m_ShadowSize(VEC3_RESET_ZERO)									//�e�̃T�C�Y
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�e�����o�ϐ�������
}

//=============================================
//�f�X�g���N�^
//=============================================
CCharacter::~CCharacter()
{
	if (m_pMove != nullptr)
	{
		delete m_pMove;
	}
	if (m_pGunAttack != nullptr)
	{
		delete m_pGunAttack;
	}
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
	}
	if (m_pStan != nullptr)
	{
		delete m_pStan;
	}
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}

	for (int i = INT_ZERO; i < MAX_PARTS; i++)
	{
		if (m_apModel[i] != nullptr)
		{
			m_apModel[i]->Unload();
		}
	}
}

//=============================================
//������
//=============================================
HRESULT CCharacter::Init()
{
	if (m_pCharacterState == nullptr)
	{
		m_pCharacterState = new CMoveState;
	}
	if (m_pShadow == nullptr)
	{
		m_pShadow = CShadow::Create({ GetPos().x,SHADOW_POS_Y,GetPos().z }, m_ShadowSize);
	}

	//�e�̃T�C�Y�ݒ�
	m_pShadow->SetSize({ m_ShadowSize });

	//�ŏ��ǂ̃��[�V�����ł��Ȃ��l����
	m_Motion = -1;
	//���[�v���[�V�����I����Ă锻���
	m_bLoopFinish = true;

	//�e�N���X�̏�����
	CObjectX::Init();

	//���[���h�}�g���b�N�X�ݒ�
	ConversionMtxWorld();
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CCharacter::Uninit()
{
	if (m_pGun != nullptr)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}

    CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CCharacter::Update()
{
	for (int nCnt = 0; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos({ m_apModel[nCnt]->GetMtxWorld()._41,m_apModel[nCnt]->GetMtxWorld()._42,m_apModel[nCnt]->GetMtxWorld()._43 });
	}

	//�d�͏���
	Gravity();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	if (m_bLanding)
	{
		//�ړ��ʂ��X�V(�����j
		m_move *= FLOAT_ONE - MOVE_FRICTION;
	}

	//�ߋ��̈ʒu�ɍ��̈ʒu����
	m_oldpos = pos;

	//�ړ��ʒǉ�
	pos += m_move;

	//���W���X�V
	SetPos(pos);

	//�e�̃T�C�Y�ݒ�
	m_pShadow->SetSize(m_ShadowSize);

	//�e�̈ʒu�ݒ�
	m_pShadow->SetPos({ GetPos().x,SHADOW_POS_Y,GetPos().z });

	//�ő�ŏ��l�擾
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	if (m_bLanding)
	{//���n���Ă�Ȃ�
		//�W�����v�����Z�b�g
		m_nJumpCnt = INT_ZERO;
	}

	//�u���b�N�Ƃ̐ڐG����
	HitBlock(m_PartsCnt);

	//���Ƃ̐ڐG����
	HitField();
}

//=============================================
//�`��
//=============================================
void CCharacter::Draw()
{
	CObjectX::Draw();
}

//=============================================
//���[�V�����p�̕`��
//=============================================
void CCharacter::MotionDraw()
{
	//�f�o�C�X�̎擾
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&MtxWorld);

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = INT_ZERO; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//=============================================
//�p�[�c�̃��[�h
//=============================================
void CCharacter::Load_Parts(const char* FileName)
{
	//�t�@�C���̓ǂݍ���
	std::ifstream File(FileName, std::ios::binary);

	//�t�@�C�����J���Ȃ�������֐��𔲂���
	if (!File.is_open())
	{
		return;
	}

	File.read(reinterpret_cast<char*>(&m_motion_data), sizeof(CCharacter::MotionData));

	m_Speed = m_motion_data.speed;
	m_Jump = m_motion_data.jump;
	m_PartsCnt = m_motion_data.parts;

	for (int nCnt = 0; nCnt < m_motion_data.parts; ++nCnt)
	{
		m_apModel[nCnt] = CModel_Parts::Create(VEC3_RESET_ZERO, VEC3_RESET_ZERO, &m_motion_data.path[nCnt][0]);
		m_apModel[nCnt]->m_nIdx = m_motion_data.idx[nCnt];
		m_apModel[nCnt]->m_nIdxModelParent = m_motion_data.parent[nCnt];

		//�e��ݒ�
		if (m_apModel[nCnt]->m_nIdxModelParent == -1)
		{
			m_apModel[nCnt]->SetParent(nullptr);
		}
		else
		{
			m_apModel[nCnt]->SetParent(m_apModel[m_apModel[nCnt]->m_nIdxModelParent]);
		}

		m_apModel[nCnt]->SetPos(m_motion_data.parts_pos[nCnt]);
		m_apModel[nCnt]->SetRot(m_motion_data.parts_rot[nCnt]);

		m_apModel[nCnt]->m_Tpos = m_apModel[nCnt]->m_pos;
		m_apModel[nCnt]->m_Trot = m_apModel[nCnt]->m_rot;
	}

	File.close();
}

//=============================================
//���[�V��������
//=============================================
void CCharacter::Motion(int NumParts)
{
	D3DXVECTOR3 MovePos[MAX_PARTS];
	D3DXVECTOR3 MoveRot[MAX_PARTS];

	int nNextKey = (m_nKeySetCnt + INT_ONE) % m_motion_data.motion_set[m_Motion].nNumKey;

	for (int nMotionCnt = INT_ZERO; nMotionCnt < m_PartsCnt; nMotionCnt++)
	{
		MovePos[nMotionCnt] = (m_motion_data.motion_set[m_Motion].keySet[nNextKey].key[nMotionCnt].pos - m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].pos) / (float)m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame;
		MoveRot[nMotionCnt] = (m_motion_data.motion_set[m_Motion].keySet[nNextKey].key[nMotionCnt].rot - m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].rot) / (float)m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame;

		m_apModel[nMotionCnt]->m_pos += MovePos[nMotionCnt];
		m_apModel[nMotionCnt]->m_rot += MoveRot[nMotionCnt];
	}

	m_nMotionFrameCnt++;

	if (m_nMotionFrameCnt > m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame)
	{

		m_nMotionFrameCnt = INT_ZERO;
		m_nKeySetCnt = (m_nKeySetCnt + INT_ONE) % m_motion_data.motion_set[m_Motion].nNumKey;
		if (m_nKeySetCnt == INT_ZERO && m_motion_data.motion_set[m_Motion].nLoop == INT_ZERO)
		{//�L�[���I��胋�[�v���[�V��������Ȃ����
			//���[�V�������j���[�g������
			SetMotion(INT_ZERO);
			//�I���������
			m_bLoopFinish = true;
		}	
	}
}

//=====================================
//�����Ŏw�肵�����[�V�����ɐ؂�ւ���
//=====================================
void CCharacter::SetMotion(int Motion)
{
	if (m_Motion == Motion)
	{//���̃��[�V�����ƈ�v���Ă�����
		//���̊֐��𔲂���
		return;
	}

	m_Motion = Motion;

	//�t���[�����Z�b�g
	m_nMotionFrameCnt = INT_ZERO;

	//�L�[�J�E���g���Z�b�g
	m_nKeySetCnt = INT_ZERO;

	if (m_motion_data.motion_set[m_Motion].nLoop == INT_ZERO)
	{
		//�I���������
		m_bLoopFinish = false;
	}

	for (int nCntParts = INT_ZERO; nCntParts < m_PartsCnt; nCntParts++)
	{
		m_apModel[nCntParts]->m_pos = m_apModel[nCntParts]->m_Tpos;
		m_apModel[nCntParts]->m_rot = m_apModel[nCntParts]->m_Trot;
		m_apModel[nCntParts]->m_rot = m_motion_data.motion_set[Motion].keySet[0].key[nCntParts].rot;
	}
}


//=============================================
//�d�͏���
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//�W�����v����
//=============================================
void CCharacter::Jump()
{
	m_move.y = m_Jump; //�W�����v�͑��
	m_bLanding = false; //�󒆏��
}

//=============================================
//�u���b�N�Ƃ̐ڐG����(�����p�[�c�p)
//=============================================
void CCharacter::HitBlock(int NumParts)
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < NumParts; ++nPartsCnt)
	{
		D3DXVECTOR3 pos = {m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43};
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
			if (pObj == nullptr)
			{//�k���|�C���^�Ȃ�
				//�I�u�W�F�N�g��T��������
				continue;
			}

			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N��T��
			if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{//�u���b�N����Ȃ����
				//�u���b�N��T��������
				continue;
			}

			//���S�Ƀ_�E���L���X�g
			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

			//�u���b�N�Ƃ̓����蔻��
			ColisionBlock_X(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);
			ColisionBlock_Z(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);
			ColisionBlock_Y(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);

			if (m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_X
				|| m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_Z)
			{
				break;
			}
		}
	}
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_X
//=============================================
void CCharacter::ColisionBlock_X(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	//�����蔻��`�F�b�N
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_X)
	{//x�����ɓ������Ă���

		SetPos({m_oldpos.x,GetPos().y,GetPos().z});

		//X���ɓ�������
		Info.bColision_X = true;

		//���������u���b�N�̏���n��
		Info.pBlock = pBlock;
	}
	else if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//X���ɓ������ĂȂ�
		Info.bColision_X = false;
	}

	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_Y
//=============================================
void CCharacter::ColisionBlock_Y(int PartsIdx, D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_UNDER_Y)
	{//y(��)�����ɓ������Ă���
		CharacterPos.y = CharacterOldPos.y;

		//Y���ɓ�������
		Info.bColision_Y = true;
	}

	if (Colision == CColision::COLISION::COLISON_TOP_Y)
	{//y(��)�����ɓ������Ă���
		CharacterPos.y = CharacterOldPos.y;
		m_move.y = FLOAT_ZERO;
		m_bLanding = true; //���n

		//Y���ɓ�������
		Info.bColision_Y = true;
	}

	if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//Y���ɓ������ĂȂ�
		Info.bColision_Y = false;
	}
	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_Z
//=============================================
void CCharacter::ColisionBlock_Z(int PartsIdx, D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_Z)
	{//z�����ɓ������Ă���
		SetPos({GetPos().x,GetPos().y,m_oldpos.z});

		//Z���ɓ�������
		Info.bColision_Z = true;

		//���������u���b�N�̏���n��
		Info.pBlock = pBlock;
		
	}
	else if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//Z���ɓ������ĂȂ�
		Info.bColision_Z = false;
	}
	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//���Ƃ̐ڐG����
//=============================================
void CCharacter::HitField()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
		{//������Ȃ����
			//����T��������
			continue;
		}

		CField* pField = dynamic_cast<CField*>(pObj);

		//���Ƃ̓����蔻��
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pField->GetPos(), pField->GetSize());

		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{//y(��)�����ɓ������Ă���
			CharacterPos.y = m_oldpos.y;
			m_move.y = FLOAT_ZERO;
			m_bLanding = true; //���n
		}
		else
		{
			m_bLanding = false; //���n
		}

		if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x + COLLISION_SLACK
			&& CharacterPos.x <= pField->GetPos().x - pField->GetSize().x + COLLISION_SLACK)
		{
			CharacterPos.x = m_oldpos.x;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x - COLLISION_SLACK
			&& CharacterPos.x >= pField->GetPos().x + pField->GetSize().x - COLLISION_SLACK)
		{
			CharacterPos.x = m_oldpos.x;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z + COLLISION_SLACK
			&& CharacterPos.z <= pField->GetPos().z - pField->GetSize().z + COLLISION_SLACK)
		{
			CharacterPos.z = m_oldpos.z;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z - COLLISION_SLACK
			&& CharacterPos.z >= pField->GetPos().z + pField->GetSize().z - COLLISION_SLACK)
		{
			CharacterPos.z = m_oldpos.z;
			m_move.x = FLOAT_ZERO;
		}
		SetPos(CharacterPos);
	}
}

//=============================================
//���C���X���[�N�Ɠ����邩�`�F�b�N
//=============================================
CCharacter::RayHitInfo CCharacter::PerformRaycast_Smoke(D3DXVECTOR3 vector, CCharacter* character)
{
	RayHitInfo Info; //�q�b�g����Ԃ��ϐ�

	//������
	Info.distance = -1.0f; //��Βl�ŕԂ�̂œ�����Ȃ��������p��-����
	Info.hit = false; //�������Ă��Ȃ���Ԃ�

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CSmokeRange::SMOKE_RANGE_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_SMOKE_RANGE)
		{//�X���[�N����Ȃ����
			//�X���[�N��T��������
			continue;
		}

		CSmokeRange* pSmoke = dynamic_cast<CSmokeRange*>(pObj);
		//���C�����_����̍��������΂�(y�̓G�l�~�[�����΂��ۂ̍�������)
		D3DXVECTOR3 StartRay = { character->GetPos().x - pSmoke->GetPos().x,character->GetPos().y + RAY_CORRECTION_VALUE,character->GetPos().z - pSmoke->GetPos().z };

		D3DXIntersect(pSmoke->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);

		if (Info.hit)
		{
			// ��Q�����Ԃɂ���ꍇ
			return Info;
		}
	}
	// ��Q�����Ȃ��A�v���C���[�܂Ń��C�����B����ꍇ
	return Info;
}

//=============================================
//���C���u���b�N�Ɠ����邩�`�F�b�N
//=============================================
CCharacter::RayHitInfo CCharacter::PerformRaycast_Block(D3DXVECTOR3 vector, CCharacter* character)
{
	RayHitInfo Info; //�q�b�g����Ԃ��ϐ�
	
	//������
	Info.distance = -1.0f; //��Βl�ŕԂ�̂œ�����Ȃ��������p��-����
	Info.hit = false; //�������Ă��Ȃ���Ԃ�

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
		{//�u���b�N����Ȃ����
			//�u���b�N��T��������
			continue;
		}

		CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

		//���C�����_����̍��������΂�
		D3DXVECTOR3 StartRay = { character->GetPos().x - pBlock->GetPos().x,character->GetPos().y + RAY_CORRECTION_VALUE,character->GetPos().z - pBlock->GetPos().z };
		D3DXIntersect(pBlock->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
		if (Info.hit)
		{
			return Info;
		}
	}
	return Info;
}

//=============================================
//���[���h�}�g���b�N�X�̕ϊ�
//=============================================
void CCharacter::ConversionMtxWorld()
{
	//�f�o�C�X�̎擾
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&MtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = INT_ZERO; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->ConversionMtxWorld();
	}
}

//=============================================
//�ǂƂ̐ڐG����_X
//=============================================
void CCharacter::ColisionWall_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//�����蔻��`�F�b�N
	CColision::COLISION Checkcolision_X = CManager::GetInstance()->GetColision()->CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_X == CColision::COLISION::COLISON_X)
	{//x�����ɓ������Ă���
		CharacterPos.x = m_oldpos.x;
		m_move.x = FLOAT_ZERO;
	}
}

//=============================================
//�ǂƂ̐ڐG����_Z
//=============================================
void CCharacter::ColisionWall_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//�����蔻��`�F�b�N
	CColision::COLISION Checkcolision_Z = CManager::GetInstance()->GetColision()->CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
	{//z�����ɓ������Ă���
		CharacterPos.z = m_oldpos.z;
		m_move.z = FLOAT_ZERO;
	}
}

//=============================================
//�L�����N�^�[�̃X�e�[�g�ύX
//=============================================
void CCharacter::ChangeState(CCharacterState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
		m_pCharacterState = state;
		m_pCharacterState->Start(this);
	}
}
