//=============================================
//
//�{�X�̓G�̏���[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

const float CBossEnemy::FIND_PLAYER_DISTANCE = 500.0f; //���̒l�܂ł�������ǂ�������
const float CBossEnemy::LOST_PLAYER_DISTANCE = 800.0f; //���̒l�ȏゾ�����猩����

//=============================================
//�R���X�g���N�^
//=============================================
CBossEnemy::CBossEnemy(int nPriority)
{
	m_pBossState = nullptr;

	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CBossGunAttack;
	}
	if (m_pTackle == nullptr)
	{
		m_pTackle = new CBossTackle;
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
	if (m_pTackle != nullptr)
	{
		delete m_pTackle;
	}
}

//=============================================
//������
//=============================================
HRESULT CBossEnemy::Init()
{
	if (m_pBossState == nullptr)
	{
		m_pBossState = new CTackleState;
	}
	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CMiniGun;

		m_pGun->Init();
	}

	SetLife(DEFAULT_LIFE);
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
	//TODO:���ʂȏ��������C��...
	m_pBossState->Chase(this);

	m_pBossState->Wandering(this);

	m_pBossState->Tackle(this);

	CEnemy::Update();

	if (GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		ChangeState(new CChaseState);
	}
	Motion(NUM_PARTS); //���[�V��������

}

//=============================================
//�`��
//=============================================
void CBossEnemy::Draw()
{
	m_pWandering->DrawDebug();
	m_pBossState->DrawDebug();
	m_pChase->DrawDebug();
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
		delete m_pBossState;
		m_pBossState = state;
	}
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
			CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�I�u�W�F�N�g�ɗv�f�������Ă�����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�u���b�N�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					//���S�Ƀ_�E���L���X�g
					CPlayer_test* pPlayer = dynamic_cast<CPlayer_test*>(pObj);

					CheckColisionPlayer(pPlayer, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

//=============================================
//�v���C���[�Ƃ̓����蔻��
//=============================================
void CBossEnemy::CheckColisionPlayer(CPlayer_test* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
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
			// X���Փˎ��̏���
			pPlayer->SetMove({0.0f,20.0f,0.0f});
			pPlayer->Damage(m_pTackle->TACKLE_DAMAGE);
		}
	}
}
