//=============================================
//
//�{�X�̓G�̏���[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

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
m_pTackleEffect(nullptr),									//�_�b�V���G�t�F�N�g
m_pTackleCharge(nullptr)								//�^�b�N���O�̃G�t�F�N�g
{
	//�e�s�����쐬
	CreateBossStrategy();
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossEnemy::~CBossEnemy()
{
	//�X�e�[�g�j��
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
	}

	//�e�s���̔j��
	DeleteBossStrategy();

	//�^�b�N���G�t�F�N�g�j��
	if (m_pTackleEffect != nullptr)
	{
		m_pTackleEffect->Uninit();
		m_pTackleEffect = nullptr;
	}

	//�^�b�N���O�̃G�t�F�N�g�j��
	if (m_pTackleCharge != nullptr)
	{
		m_pTackleCharge->Uninit();
		m_pTackleCharge = nullptr;
	}
}

//=============================================
//�{�X�̍s���쐬
//=============================================
void CBossEnemy::CreateBossStrategy()
{
	//�{�X�̜p�j�s���𐶐�
	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	//�{�X�̒ǐՍs���𐶐�
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	//�{�X�̍����s���𐶐�
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CBossConfusion;
	}
	//�{�X�̃X�^���s���𐶐�
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	//�{�X�̎ˌ��s���𐶐�
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CBossGunAttack;
	}
	//�{�X�̃^�b�N���s���𐶐�
	if (m_pTackle == nullptr)
	{
		m_pTackle = new CBossTackle;
	}
	//�{�X�̖\���s�����쐬
	if (m_pRampage == nullptr)
	{
		m_pRampage = new CBossRampage;
	}
	//�{�X�̑{���s�����쐬
	if (m_pSearch == nullptr)
	{
		m_pSearch = new CBossSearch;
	}
}

//=============================================
// �e�s���̔j��
//=============================================
void CBossEnemy::DeleteBossStrategy()
{
	//�p�j�s���j��
	if (m_pWandering != nullptr)
	{
		delete m_pWandering;
	}
	//�ǐՍs���j��
	if (m_pChase != nullptr)
	{
		delete m_pChase;
	}
	//�����s���j��
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}
	//�^�b�N���s���j��
	if (m_pTackle != nullptr)
	{
		delete m_pTackle;
	}
	//�\���s���j��
	if (m_pRampage != nullptr)
	{
		delete m_pRampage;
	}
	//�T���s���j��
	if (m_pSearch != nullptr)
	{
		delete m_pSearch;
	}
}

//=============================================
//������
//=============================================
HRESULT CBossEnemy::Init()
{
	//�{�X�̃X�e�[�g����
	if (m_pBossState == nullptr)
	{
		//�ŏ��͜p�j���
		m_pBossState = new CWanderingState;
	}
	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CMiniGun;

		m_pGun->Init();
	}

	//�萔�l�Ō��߂��Ă��鏉���̗͐ݒ�
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
	//�e�N���X�̍X�V�������Ă�
	CEnemy::Update();

	ProcessState(); //�e�X�e�[�g�̎��s����

	Motion(NUM_PARTS); //���[�V��������

	for (int nCnt = INT_ZERO; nCnt < GetNumParts(); nCnt++)
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
	//���݂̃X�e�[�g�̜p�j�̏������Ă�
	m_pBossState->Wandering(this);

	//���݂̃X�e�[�g�̒ǐՂ̏������Ă�
	m_pBossState->Chase(this);

	//���݂̃X�e�[�g�̃X�^���̏������Ă�
	m_pBossState->Stan(this);

	//���݂̃X�e�[�g�̍����̏������Ă�
	m_pBossState->Confusion(this);

	//���݂̃X�e�[�g�̃^�b�N���̏������Ă�
	m_pBossState->Tackle(this);

	//���݂̃X�e�[�g�̒T���̏������Ă�
	m_pBossState->Search(this);

	//���݂̃X�e�[�g�̖\���̏������Ă�
	m_pBossState->Rampage(this);
}

//=============================================
//�`��
//=============================================
void CBossEnemy::Draw()
{
	//�f�o�b�O�\��
	DrawDebug();
	//�e�N���X�̕`�揈�����Ă�
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
		//�j���R����Ȃ������߂ɔj������֐������s
		m_pBossState->End(this);
		delete m_pBossState;
		m_pBossState = state;
		//�ŏ��̈�񂾂��Ăт����֐������s
		m_pBossState->Start(this);
	}
}

//=============================================
//�^�b�N���̏���
//=============================================
void CBossEnemy::TackleAction()
{
	SetMotion(CBossEnemy::MOTION_TACKLE);

	if (m_pTackleEffect == nullptr)
	{
		float fAngle = atan2f(sinf(GetRot().y), cosf(GetRot().y));

		//�_�b�V���G�t�F�N�g����
		m_pTackleEffect = CDashEffect::Create({m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - CORRECTION_VALUE_Y,m_apModel[3]->GetMtxWorld()._43 }
		, { FLOAT_ZERO,fAngle,FLOAT_ZERO });
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʉ��Z
	move.x += sinf(GetRot().y) *  GetSpeed() * -TACKLE_VALUE;
	move.z += cosf(GetRot().y) *  GetSpeed() * -TACKLE_VALUE;

	//�ړ��ʑ��
	SetMove(move);

	if ( m_pTackleEffect != nullptr)
	{//�G�t�F�N�g����������
	 //�G�t�F�N�g�𓮂���
		 m_pTackleEffect->SetPos({ m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - CORRECTION_VALUE_Y,m_apModel[3]->GetMtxWorld()._43 });
	}

	//�����̕������擾
	D3DXVECTOR3 vec = { sinf( GetRot().y + D3DX_PI), INT_ZERO, cosf( GetRot().y + D3DX_PI) };

	//�v���C���[�Ƃ̔���`�F�b�N
	 ColisionPlayer();
}

//=============================================
//�v���C���[�Ƃ̓����蔻��
//=============================================
void CBossEnemy::ColisionPlayer()
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		//�ŏ��l�擾
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		//�ő�l�擾
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();

		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
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
	for (int nPartsCnt = INT_ZERO; nPartsCnt < pPlayer->GetNumParts(); nPartsCnt++)
	{//�p�[�c����
		//�v���C���[�̃��[���h�}�g���b�N�X�̈ʒu���擾
		D3DXVECTOR3 playerpos = { pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._41,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._42,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._43 };

		//�ŏ��l�擾
		D3DXVECTOR3 PlayerMinpos = pPlayer->m_apModel[nPartsCnt]->GetMin();

		//�ő�l�擾
		D3DXVECTOR3 PlayerMaxpos = pPlayer->m_apModel[nPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			playerpos, PlayerMinpos, PlayerMaxpos);

		if (colision == CColision::COLISION::COLISON_Z || colision == CColision::COLISION::COLISON_X)
		{//�������Ă�����
			//�v���C���[�𐁂���΂�
			D3DXVECTOR3 Playermove = D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * PLAYER_KNOCKBACK_SPEED,
				PLAYER_KNOCKBACK_Y, cosf(GetRot().y + D3DX_PI) * PLAYER_KNOCKBACK_SPEED);

			//�ړ��ʂ�ݒ�
			pPlayer->SetMove(Playermove);
			//�v���C���[�̃X�e�[�g�𐁂���΂���Ԃ�
			pPlayer->ChangePlayerState(new CBlownState);
			//�_���[�W��^����
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

	for (int nPartsCnt = INT_ZERO; nPartsCnt < NumParts; ++nPartsCnt)
	{//�p�[�c����
		//�����̃��[���h�}�g���b�N�X�̈ʒu���擾
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		//�ߋ��̈ʒu�擾
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		//�ŏ��l�擾
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		//�ő�l�擾
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();

		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
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
	for (int nCntParts = INT_ZERO; nCntParts < GetNumParts(); nCntParts++)
	{//�p�[�c����
		//�������Ă��Ȃ���Ԃ�
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
