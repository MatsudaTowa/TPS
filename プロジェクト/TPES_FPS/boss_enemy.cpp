//=============================================
//
//�{�X�̓G�̏���[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

const float CBossEnemy::FIND_PLAYER_DISTANCE = 300.0f; //���̒l�܂ł�������ǂ�������
const float CBossEnemy::LOST_PLAYER_DISTANCE = 100.0f; //���̒l�ȏゾ�����猩����
//�e�̃T�C�Y
const D3DXVECTOR3 CBossEnemy::SHADOW_SIZE = { 30.0f, 0.0, 30.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CBossEnemy::CBossEnemy(int nPriority):CEnemy(nPriority),
m_pChase(nullptr),										//�ǐՏ���
m_pWandering(nullptr),									//�p�j����
m_pConfusion(nullptr),									//��������
m_pTackle(nullptr),										//�^�b�N������
m_pSearch(nullptr),										//�T������
m_pRampage(nullptr),									//�\������
m_pDashEffect(nullptr),									//�_�b�V���G�t�F�N�g
m_pTackleCharge(nullptr)								//�^�b�N���O�̃G�t�F�N�g
{
	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CBossConfusion;
	}
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CBossGunAttack;
	}
	if (m_pTackle == nullptr)
	{
		m_pTackle = new CBossTackle;
	}
	if (m_pRampage == nullptr)
	{
		m_pRampage = new CBossRampage;
	}
	if (m_pSearch == nullptr)
	{
		m_pSearch = new CBossSearch;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossEnemy::~CBossEnemy()
{
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
	}
	if (m_pWandering != nullptr)
	{
		delete m_pWandering;
	}
	if (m_pChase != nullptr)
	{
		delete m_pChase;
	}
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}
	if (m_pTackle != nullptr)
	{
		delete m_pTackle;
	}
	if (m_pRampage != nullptr)
	{
		delete m_pRampage;
	}
	if (m_pSearch != nullptr)
	{
		delete m_pSearch;
	}
	if (m_pDashEffect != nullptr)
	{
		m_pDashEffect->Uninit();
		m_pDashEffect = nullptr;
	}
	if (m_pTackleCharge != nullptr)
	{
		m_pTackleCharge->Uninit();
		m_pTackleCharge = nullptr;
	}
}

//=============================================
//������
//=============================================
HRESULT CBossEnemy::Init()
{
	if (m_pBossState == nullptr)
	{
		m_pBossState = new CWanderingState;
	}
	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CMiniGun;

		m_pGun->Init();
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
void CBossEnemy::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBossEnemy::Update()
{
	CEnemy::Update();

	ProcessState(); //�e�X�e�[�g�̎��s����

	Motion(NUM_PARTS); //���[�V��������

#ifdef _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_9))
	{
		SetLife(300);
	}
#endif // _DEBUG


	for (int nCnt = 0; nCnt < GetNumParts(); nCnt++)
	{
		if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_X)
		{
			m_HitAxis = X;
			break;
		}
		else if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_Z)
		{
			m_HitAxis = Z;
			break;
		}
		else
		{
			m_HitAxis = NONE;
		}
	}
}

//=============================================
//�X�e�[�g�̎��s����
//=============================================
void CBossEnemy::ProcessState()
{
	m_pBossState->Chase(this);

	m_pBossState->Wandering(this);

	m_pBossState->Stan(this);

	m_pBossState->Confusion(this);

	m_pBossState->Tackle(this);

	m_pBossState->Search(this);

	m_pBossState->Rampage(this);
}

//=============================================
//�`��
//=============================================
void CBossEnemy::Draw()
{
	//�f�o�b�O�\��
	DrawDebug();
	CEnemy::Draw();
}

//=============================================
//�{�X�̏�Ԑ؂�ւ�
//=============================================
void CBossEnemy::ChangeState(CBossState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pBossState != nullptr)
	{
		m_pBossState->End(this);
		delete m_pBossState;
		m_pBossState = state;
		m_pBossState->Start(this);
	}
}

//=============================================
//�^�b�N���̏���
//=============================================
void CBossEnemy::TackleAction()
{
	SetMotion(CBossEnemy::MOTION_TACKLE);

	if (m_pDashEffect == nullptr)
	{
		float fAngle = atan2f(sinf(GetRot().y), cosf(GetRot().y));

		//�_�b�V���G�t�F�N�g����
		m_pDashEffect = CDashEffect::Create({m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - 100.0f,m_apModel[3]->GetMtxWorld()._43 }
		, { 0.0f,fAngle,0.0f });
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʉ��Z
	move.x += sinf(GetRot().y) *  GetSpeed() * -15.0f;
	move.z += cosf(GetRot().y) *  GetSpeed() * -15.0f;

	//�ړ��ʑ��
	SetMove(move);

	if ( m_pDashEffect != nullptr)
	{//�G�t�F�N�g����������
	 //�G�t�F�N�g�𓮂���
		 m_pDashEffect->SetPos({ m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - 100.0f,m_apModel[3]->GetMtxWorld()._43 });
	}

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf( GetRot().y + D3DX_PI), 0.0f, cosf( GetRot().y + D3DX_PI) };

	//�v���C���[�Ƃ̔���`�F�b�N
	 ColisionPlayer();
}

//=============================================
//�v���C���[�Ƃ̓����蔻��
//=============================================
void CBossEnemy::ColisionPlayer()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�I�u�W�F�N�g�ɗv�f�������Ă�����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�u���b�N�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					//���S�Ƀ_�E���L���X�g
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

					if (pPlayer->GetEnemyColision())
					{//�v���C���[���G�l�~�[�Ɠ������Ԃ̂Ƃ�
						CheckColisionPlayer(pPlayer, nPartsCnt, pos, Minpos, Maxpos);
					}
				}
			}
		}
	}
}

//=============================================
//�v���C���[�Ƃ̓����蔻��`�F�b�N
//=============================================
void CBossEnemy::CheckColisionPlayer(CPlayer* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nPartsCnt = 0; nPartsCnt < pPlayer->GetNumParts(); nPartsCnt++)
	{
		D3DXVECTOR3 playerpos = { pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._41,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._42,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 PlayerMinpos = pPlayer->m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 PlayerMaxpos = pPlayer->m_apModel[nPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			playerpos, PlayerMinpos, PlayerMaxpos);

		if (colision == CColision::COLISION::COLISON_Z || colision == CColision::COLISION::COLISON_X)
		{
			D3DXVECTOR3 Playermove = D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 15.0f,
				30.0f, cosf(GetRot().y + D3DX_PI) * 15.0f);
			// X���Փˎ��̏���
			pPlayer->SetMove(Playermove);
			pPlayer->ChangePlayerState(new CBlownState);
			pPlayer->Damage(m_pTackle->TACKLE_DAMAGE);
		}
	}
}
//=============================================
//�E���g�q�b�g����
//=============================================
void CBossEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	ChangeState(new CBossStanState);
	//�e�N���X�̃q�b�g����
	CEnemy::MediumUltHit(UltPos, nDamage);
}

//=============================================
//�u���b�N�Ƃ̔���
//=============================================
void CBossEnemy::HitBlock(int NumParts)
{
	CCharacter::HitBlock(NumParts);

	for (int nPartsCnt = 0; nPartsCnt < NumParts; ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_X
				|| m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_Z)
			{
				
				break;
			}
		}
	}
}

//=============================================
//�������ĂȂ������
//=============================================
void CBossEnemy::ColisionReset()
{
	for (int nCntParts = 0; nCntParts < GetNumParts(); nCntParts++)
	{
		m_apModel[nCntParts]->GetColisionBlockInfo().bColision_X = false;
		m_apModel[nCntParts]->GetColisionBlockInfo().bColision_Z = false;
	}
}

//=============================================
//�{�X�̃f�o�b�O�\��
//=============================================
void CBossEnemy::DrawDebug()
{
#ifdef _DEBUG
	m_pWandering->DrawDebug();
	m_pBossState->DrawDebug();
	m_pChase->DrawDebug();
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	for (int nCnt = 0; nCnt < GetNumParts(); nCnt++)
	{
		if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_X)
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f �����蔻��:X", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
		else if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_Z)
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f �����蔻��:Z", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
		else
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f �����蔻��:�������ĂȂ�", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
	}

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
