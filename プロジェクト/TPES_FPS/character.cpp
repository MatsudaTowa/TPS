//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "field.h"
#include "colision.h"
#include "smoke_range.h"

//�{�X���X���W
const float CCharacter::BOSS_FIELD_X = 600.0f;
//�d�͒l
const float CCharacter::GRAVITY_MOVE = 1.5f;
//�d�͍ő�l
const float CCharacter::GRAVITY_MAX = 20.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority),m_bLanding(false),m_bWay(false),m_move(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_nLife(0)
,m_nStateCnt(0),m_oldpos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_State(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL), 
m_PartsCnt(0), m_nMotionFrameCnt(0), m_nKeySetCnt(0), m_Motion(0), m_bLoopFinish(),m_Speed(), 
m_Jump(), m_pGun(),m_MotionSet(), m_pMove(),m_pGunAttack(), m_pCharacterState(), m_nJumpCnt(0),m_Colision(CColision::COLISION::COLISON_NONE)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�e�����o�ϐ�������
	m_pMove = nullptr;
	m_pGunAttack = nullptr;
	m_pCharacterState = nullptr;
	m_pStan = nullptr;
	m_pConfusion = nullptr;
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

	for (int i = 0; i < 64; i++)
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
	//�ŏ��ǂ̃��[�V�����ł��Ȃ��l����
	m_Motion = -1;
	//���[�v���[�V�����I����Ă锻���
	m_bLoopFinish = true;
	//�e�N���X�쐬
	//m_pGun = new CGun;
	//�e�N���X�̏�����
	CObjectX::Init();
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

	//�ړ��ʂ��X�V(�����j
	m_move *= 1.0f - 0.3f;

	//�ߋ��̈ʒu�ɍ��̈ʒu����
	m_oldpos = pos;

	//�ړ��ʒǉ�
	pos += m_move;

	//���W���X�V
	SetPos(pos);

	//�ő�ŏ��l�擾
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	if (m_bLanding)
	{//���n���Ă�Ȃ�
		//�W�����v�����Z�b�g
		m_nJumpCnt = 0;
	}

	//�u���b�N�Ƃ̐ڐG����
	HitBlock(m_PartsCnt);

	//���Ƃ̐ڐG����
	HitField();

	//�ǂƂ̐ڐG����
	HitWall();
}

//=============================================
//�`��
//=============================================
void CCharacter::Draw()
{
	switch (m_State)
	{
	case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
		CObjectX::Draw();
		break;
	case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
		//�_���[�W��Ԃ̐F�ɕύX
		CObjectX::Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}

//=============================================
//���[�V�����p�̕`��
//=============================================
void CCharacter::MotionDraw()
{
	//�f�o�C�X�̎擾
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
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

	for (int nCnt = 0; nCnt < m_PartsCnt; nCnt++)
	{
		switch (m_State)
		{
		case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
			m_apModel[nCnt]->Draw();
			break;
		case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
			//�_���[�W��Ԃ̐F�ɕύX
			m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
	}
}

//=============================================
//���[�V�����p�̕`��(�F�t��)
//=============================================
void CCharacter::MotionDraw(D3DXCOLOR col)
{
	//�f�o�C�X�̎擾
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
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

	for (int nCnt = 0; nCnt < m_PartsCnt; nCnt++)
	{
		switch (m_State)
		{
		case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
			m_apModel[nCnt]->Draw(col);
			break;
		case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
			//�_���[�W��Ԃ̐F�ɕύX
			m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
	}
}

//=============================================
//�p�[�c�̃��[�h
//=============================================
void CCharacter::Load_Parts(const char* FileName)
{
	int nCnt = 0;
	int nCntName = 0;
	int nCntKey = 0; //�L�[������p�[�c�̃J�E���g��
	int nCntMotion = 0; //�L�[���̃J�E���g
	int nCntMotionSet = 0; //���[�V�����̎�ނ̃J�E���g
	char aDataSearch[256];
	char aEqual[256]; //[��]�ǂݍ��ݗp
	char aGets[256]; //���[�V�����̂���Ȃ����̓ǂݍ��ݗp
	float speed = 0.0f;//�ړ���
	float jump = 0.0f;//�W�����v��
	float radius = 0.0f;//���a
	float height = 0.0f;//����

	char Path[MAX_PARTS][256]; //�p�[�c�̃p�X

	//�t�@�C���̓ǂݍ���
	FILE* pFile;

	//�t�@�C���̓ǂݍ���
	pFile = fopen(FileName, "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}

	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_MODEL"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &m_PartsCnt);
		}
		if (!strcmp(aDataSearch, "MODEL_FILENAME"))
		{//���f���t�@�C���ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%s", &Path[nCntName][0]);
			//���f���p�[�c�̃N���G�C�g
			m_apModel[nCntName] = CModel_Parts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &Path[nCntName][0]);

			nCntName++;
		}

		if (!strcmp(aDataSearch, "CHARACTERSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_CHARACTERSET"))
				{
					break;
				}
				else if (!strcmp(aDataSearch, "MOVE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &m_Speed);
				}
				else if (!strcmp(aDataSearch, "JUMP"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &m_Jump);
				}
				else if (!strcmp(aDataSearch, "RADIUS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &radius);
				}
				else if (!strcmp(aDataSearch, "HEIGHT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &height);
				}
				else if (!strcmp(aDataSearch, "PARTSSET"))
				{
					//���ڂ��Ƃ̃f�[�^����
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); //����

						if (!strcmp(aDataSearch, "END_PARTSSET"))
						{
							break;
						}
						else if (!strcmp(aDataSearch, "INDEX"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_apModel[nCnt]->m_nIdx);
						}
						else if (!strcmp(aDataSearch, "PARENT"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_apModel[nCnt]->m_nIdxModelParent);

							//�e��ݒ�
							if (m_apModel[nCnt]->m_nIdxModelParent == -1)
							{
								m_apModel[nCnt]->SetParent(nullptr);
							}
							else
							{
								m_apModel[nCnt]->SetParent(m_apModel[m_apModel[nCnt]->m_nIdxModelParent]);
							}

						}
						else if (!strcmp(aDataSearch, "POS"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f %f %f",
								&m_apModel[nCnt]->m_pos.x,
								&m_apModel[nCnt]->m_pos.y,
								&m_apModel[nCnt]->m_pos.z);

							m_apModel[nCnt]->SetPos(m_apModel[nCnt]->m_pos);

							m_apModel[nCnt]->m_Tpos = m_apModel[nCnt]->m_pos;
						}
						else if (!strcmp(aDataSearch, "ROT"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f %f %f",
								&m_apModel[nCnt]->m_rot.x,
								&m_apModel[nCnt]->m_rot.y,
								&m_apModel[nCnt]->m_rot.z);

							m_apModel[nCnt]->SetRot(m_apModel[nCnt]->m_rot);

							m_apModel[nCnt]->m_Trot = m_apModel[nCnt]->m_rot;

						}
					}
					nCnt++; //�f�[�^�����Z
				}
			}
		}
		if (!strcmp(aDataSearch, "MOTIONSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_MOTIONSET"))
				{
					nCntMotion = 0;
					break;
				}
				else if (!strcmp(aDataSearch, "LOOP"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].nLoop);
				}
				else if (!strcmp(aDataSearch, "NUM_KEY"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].nNumKey);

				}
				else if (!strcmp(aDataSearch, "KEYSET"))
				{
					fgets(&aGets[0], 39, pFile);

					//���ڂ��Ƃ̃f�[�^����
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); //����

						if (!strcmp(aDataSearch, "END_KEYSET"))
						{
							nCntKey = 0;
							break;
						}

						else if (!strcmp(aDataSearch, "FRAME"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].nFrame);
						}
						else if (!strcmp(aDataSearch, "KEY"))
						{
							//���ڂ��Ƃ̃f�[�^����
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch);

								if (!strcmp(aDataSearch, "END_KEY"))
								{
									break;
								}
								else if (!strcmp(aDataSearch, "POS"))
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f %f %f", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.x,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.y,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.z);
								}
								else if (!strcmp(aDataSearch, "ROT"))
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f %f %f", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.x,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.y,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.z);
								}
							}
							nCntKey++; //�p�[�c�����Z
						}
					}
					nCntMotion++; //�L�[�����Z
				}
			}
			nCntMotionSet++; //�L�[�^�C�v�����Z
		}
	}
}

//=============================================
//���[�V��������
//=============================================
void CCharacter::Motion(int NumParts)
{
	D3DXVECTOR3 MovePos[MAX_PARTS];
	D3DXVECTOR3 MoveRot[MAX_PARTS];

	int nNextKey = (m_nKeySetCnt + 1) % m_MotionSet[m_Motion].nNumKey;

	for (int nMotionCnt = 0; nMotionCnt < m_PartsCnt; nMotionCnt++)
	{
		MovePos[nMotionCnt] = (m_MotionSet[m_Motion].keySet[nNextKey].key[nMotionCnt].pos - m_MotionSet[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].pos) / (float)m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame;
		MoveRot[nMotionCnt] = (m_MotionSet[m_Motion].keySet[nNextKey].key[nMotionCnt].rot - m_MotionSet[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].rot) / (float)m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame;

		m_apModel[nMotionCnt]->m_pos += MovePos[nMotionCnt];
		m_apModel[nMotionCnt]->m_rot += MoveRot[nMotionCnt];
		//Pos.x += MovePos[nMotionCnt].x;
		//SetPos(Pos);
	}

	m_nMotionFrameCnt++;

	if (m_nMotionFrameCnt > m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame)
	{

		m_nMotionFrameCnt = 0;
		m_nKeySetCnt = (m_nKeySetCnt + 1) % m_MotionSet[m_Motion].nNumKey;
		if (m_nKeySetCnt == 0 && m_MotionSet[m_Motion].nLoop == 0)
		{//�L�[���I��胋�[�v���[�V��������Ȃ����
			//���[�V�������j���[�g������
			SetMotion(0);
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
	if (m_Motion != Motion)
	{
		m_Motion = Motion;

		//�t���[�����Z�b�g
		m_nMotionFrameCnt = 0;

		//�L�[�J�E���g���Z�b�g
		m_nKeySetCnt = 0;

		if (m_MotionSet[m_Motion].nLoop == 0)
		{
			//�I���������
			m_bLoopFinish = false;
		}

		for (int nCntParts = 0; nCntParts < m_PartsCnt; nCntParts++)
		{
			m_apModel[nCntParts]->m_pos = m_apModel[nCntParts]->m_Tpos;
			m_apModel[nCntParts]->m_rot = m_apModel[nCntParts]->m_Trot;
			m_apModel[nCntParts]->m_rot = m_MotionSet[Motion].keySet[0].key[nCntParts].rot;
		}
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
//�u���b�N�Ƃ̐ڐG����
//=============================================
void CCharacter::HitBlock()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();
	BOOL hit;
	FLOAT distance;

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�I�u�W�F�N�g�ɗv�f�������Ă�����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				//���S�Ƀ_�E���L���X�g
				CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

				//�e���̓����蔻�� TODO:����̂Ƃ��������肷��
				ColisionBlock_X(CharacterPos, m_oldpos, CharacterMin, CharacterMax, pBlock);
				ColisionBlock_Z(CharacterPos, m_oldpos, CharacterMin, CharacterMax, pBlock);
				ColisionBlock_Y(CharacterPos, m_oldpos, CharacterMin, CharacterMax, pBlock);
			}
		}
	}

	SetPos(CharacterPos);
}

//=============================================
//�u���b�N�Ƃ̐ڐG����(�����p�[�c�p)
//=============================================
void CCharacter::HitBlock(int NumParts)
{
	for (int nPartsCnt = 0; nPartsCnt < NumParts; ++nPartsCnt)
	{
		D3DXVECTOR3 pos = {m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43};
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�I�u�W�F�N�g�ɗv�f�������Ă�����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�u���b�N�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
				{
					//���S�Ƀ_�E���L���X�g
					CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

					//�e���̓����蔻��
					ColisionBlock_X(pos, oldpos, Minpos, Maxpos, pBlock);
					ColisionBlock_Z(pos, oldpos, Minpos, Maxpos, pBlock);
					ColisionBlock_Y(pos, oldpos, Minpos, Maxpos, pBlock);
				}
			}
		}
	}
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_X
//=============================================
void CCharacter::ColisionBlock_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	//�����蔻��`�F�b�N
	m_Colision = CManager::GetInstance()->GetColision()->CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	if (m_Colision == CColision::COLISION::COLISON_X)
	{//x�����ɓ������Ă���
		CharacterPos.x = CharacterOldPos.x + pBlock->GetMinPos().x;
		m_move.x = 0.0f;
		SetPos({ m_oldpos.x,GetPos().y,GetPos().z });
	}
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_Y
//=============================================
void CCharacter::ColisionBlock_Y(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	m_Colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

	if (m_Colision == CColision::COLISION::COLISON_UNDER_Y)
	{//y(��)�����ɓ������Ă���
		CharacterPos.y = CharacterOldPos.y;
	}

	if (m_Colision == CColision::COLISION::COLISON_TOP_Y)
	{//y(��)�����ɓ������Ă���
		CharacterPos.y = CharacterOldPos.y;
		m_move.y = 0.0f;
		m_bLanding = true; //���n
	}
}

//=============================================
//�u���b�N�Ƃ̐ڐG����_Z
//=============================================
void CCharacter::ColisionBlock_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	m_Colision = CManager::GetInstance()->GetColision()->CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

	if (m_Colision == CColision::COLISION::COLISON_Z)
	{//z�����ɓ������Ă���
		CharacterPos.z = CharacterOldPos.z + pBlock->GetMaxPos().x;
		m_move.z = 0.0f;
		SetPos({GetPos().x,GetPos().y,m_oldpos.z});
	}
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

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N�Ƃ̓����蔻��
			//���Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = dynamic_cast<CField*>(pObj);

				//���݂̂������[�J����
				CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pField->GetPos(), pField->GetSize());

				if (colision == CColision::COLISION::COLISON_TOP_Y)
				{//y(��)�����ɓ������Ă���
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //���n
				}

				//TODO:�ǂ̓����蔻�������炱����g���K�v�Ȃ��Ȃ�
				{
					if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
						&& CharacterPos.x < pField->GetPos().x - pField->GetSize().x)
					{
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}

					if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
						&& CharacterPos.x > pField->GetPos().x + pField->GetSize().x)
					{
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}


					if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z
						&& CharacterPos.z < pField->GetPos().z - pField->GetSize().z)
					{
						CharacterPos.z = m_oldpos.z;
						m_move.x = 0.0f;
					}

					if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z
						&& CharacterPos.z > pField->GetPos().z + pField->GetSize().z)
					{
						CharacterPos.z = m_oldpos.z;
						m_move.x = 0.0f;
					}
				}
				
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//�ǂƂ̐ڐG����
//=============================================
void CCharacter::HitWall()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CWall::WALL_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N�Ƃ̓����蔻��
			//���Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_WALL)
			{
				CWall* pWall = dynamic_cast<CWall*>(pObj);

				ColisionWall_X(CharacterPos, CharacterMin, CharacterMax, pWall);
				ColisionWall_Z(CharacterPos, CharacterMin, CharacterMax, pWall);
			}
		}
	}
	SetPos(CharacterPos);
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

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CSmokeRange::SMOKE_RANGE_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_SMOKE_RANGE)
			{
				CSmokeRange* pSmoke = dynamic_cast<CSmokeRange*>(pObj);
				//���C�����_����̍��������΂�(y�̓G�l�~�[�����΂��ۂ̍�������)
				D3DXVECTOR3 StartRay = { character->GetPos().x - pSmoke->GetPos().x,character->GetPos().y + 20.0f,character->GetPos().z - pSmoke->GetPos().z };

				D3DXIntersect(pSmoke->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);

				if (Info.hit == true)
				{
					// ��Q�����Ԃɂ���ꍇ
					return Info;
				}
			}
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

				//���C�����_����̍��������΂�
				D3DXVECTOR3 StartRay = character->GetPos() - pBlock->GetPos();
				D3DXIntersect(pBlock->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
				if (Info.hit == true)
				{
					return Info;
				}
			}
		}
	}
	return Info;
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
		m_move.x = 0.0f;
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
		m_move.z = 0.0f;
	}
}

//=============================================
//�ړ��ʎ擾
//=============================================
D3DXVECTOR3& CCharacter::GetMove()
{
    return m_move;
}

//=============================================
//�ߋ��̈ʒu�擾
//=============================================
D3DXVECTOR3& CCharacter::GetOldPos()
{
    return m_oldpos;
}

//=============================================
//���n���Ă邩�ǂ����擾
//=============================================
bool& CCharacter::GetLaunding()
{
    return m_bLanding;
}

//=============================================
//�ǂ��������Ă邩�ǂ������擾(true:�Efalse:��)
//=============================================
bool& CCharacter::GetWay()
{
    return m_bWay;
}

//=============================================
//�I����Ă邩�擾
//=============================================
bool& CCharacter::GetFinish()
{
	return m_bLoopFinish;
}

//=============================================
//�̗͎擾
//=============================================
int& CCharacter::GetLife()
{
	return m_nLife;
}

//=============================================
//�p�[�c���擾
//=============================================
int& CCharacter::GetNumParts()
{
	return m_PartsCnt;
}

//=============================================
//�X�s�[�h�擾
//=============================================
float& CCharacter::GetSpeed()
{
	return m_Speed;	
}

//=============================================
//��Ԏ擾
//=============================================
CCharacter::CHARACTER_STATE& CCharacter::GetState()
{
	return m_State;
}

//=============================================
//�X�e�[�g�J�E���g�擾
//=============================================
int& CCharacter::GetStateCnt()
{
	return m_nStateCnt;
}

//=============================================
//�W�����v���擾
//=============================================
int& CCharacter::GetJumpCnt()
{
	return m_nJumpCnt;
}

//=============================================
//�����蔻��擾
//=============================================
CColision::COLISION& CCharacter::GetColision()
{
	return m_Colision;
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
