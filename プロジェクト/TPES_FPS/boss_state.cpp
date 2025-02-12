//=============================================
//
//�{�X�̃X�e�[�g�p�^�[��[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBossState::CBossState()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossState::~CBossState()
{
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CBossState::Start(CBossEnemy* boss)
{
}

//=============================================
//�Ō�ɌĂ΂��֐�
//=============================================
void CBossState::End(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̒ǐՏ��(���ł͉������Ȃ�)
//=============================================
void CBossState::Chase(CBossEnemy* boss)
{
}

//=============================================
//�X�^�����
//=============================================
void CBossState::Stan(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̜p�j���(���ł͉������Ȃ�)
//=============================================
void CBossState::Wandering(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̍������(���ł͉������Ȃ�)
//=============================================
void CBossState::Confusion(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̃^�b�N�����(���ł͉������Ȃ�)
//=============================================
void CBossState::Tackle(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̃v���C���[��T�����
//=============================================
void CBossState::Search(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̖\�����
//=============================================
void CBossState::Rampage(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̃f�o�b�O���
//=============================================
void CBossState::DrawDebug()
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CChaseState::CChaseState() : m_PlayTackleCnt(0)
{
	m_PlayTackleCnt = 0;
}

//=============================================
//�f�X�g���N�^
//=============================================
CChaseState::~CChaseState()
{
}

//=============================================
//�{�X�̒ǐՏ��
//=============================================
void CChaseState::Chase(CBossEnemy* boss)
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
				if (boss->m_pChase != nullptr)
				{
					boss->m_pChase->Chase(boss, pObj);
				}
			}
		}
	}

	//TODO:�X�e�[�g�p�^�[����
	++m_PlayTackleCnt;

	if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
	{//�^�b�N�����s�t���[���ɓ��B������
		//�X�e�[�g�؂�ւ�
		boss->ChangeState(new CTackleState);
		m_PlayTackleCnt = 0;
	}

	boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);
}

//=============================================
//�{�X�̒ǐՏ�ԃf�o�b�O
//=============================================
void CChaseState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n�ǐ�");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CBossStanState::Start(CBossEnemy* boss)
{
	m_StanCnt = 0;
}

//=============================================
//�Ō�ɌĂ΂��֐�
//=============================================
void CBossStanState::End(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̃X�^�����
//=============================================
void CBossStanState::Stan(CBossEnemy* boss)
{
	if (m_StanCnt < STAN_FRAME)
	{
		++m_StanCnt;

		if (boss->m_pStan != nullptr)
		{
			boss->m_pStan->Stan(boss);
		}
	}
	if (m_StanCnt >= STAN_FRAME)
	{
		m_StanCnt = 0;

		//�ˌ���ԂɑJ��
		boss->ChangeState(new CWanderingState);
	}
}

//=============================================
//�{�X�̃X�^����ԃf�o�b�O
//=============================================
void CBossStanState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n�X�^��");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CWanderingState::CWanderingState() :
	m_TransitionCnt(0),
	m_bDamage(false),
	m_TargetRot({0.0f,0.0f,0.0f})
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWanderingState::~CWanderingState()
{
}

//=============================================
//�{�X�̜p�j���
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
	if (boss->GetLife() < CBossEnemy::LOW_HP)
	{//�̗͂����Ȃ�������
		//�\����Ԃ�
		boss->ChangeState(new CRampageState);
	}
	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		m_bDamage = true;

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
			if (pObj == nullptr)
			{//�k���|�C���^�Ȃ�
				continue;
			}

			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{//�v���C���[����Ȃ�������
				continue;
			}

			CPlayer* player = dynamic_cast<CPlayer*>(pObj);

			//�v���C���[�Ƃ̋����Z�o
			D3DXVECTOR3 Distance = player->GetPos() - boss->GetPos();

			//�v���C���[�Ɍ�����p�x���Z�o
			float fAngle = atan2f(Distance.x, Distance.z);

			//�e�N���X����rot���擾
			D3DXVECTOR3 rot = boss->GetRot();

			rot.y = fAngle + D3DX_PI;

			m_TargetRot = rot;
		}
	}

	if (m_bDamage)
	{
		++m_TransitionCnt;

		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = boss->GetRot();

		boss->SetRot(rot);

		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_TransitionCnt = 0;
			boss->ChangeState(new CChaseState);
		}
	}
	else if(!m_bDamage)
	{
		if (boss->m_pWandering != nullptr)
		{
			boss->m_pWandering->Wandering(boss);
			//�v���C���[�̈ʒu�ւ̕������
			D3DXVECTOR3 Vector = boss->GetPos() + boss->GetMove() - boss->GetPos();

			if (boss->PerformRaycast_Player(Vector, boss).hit)
			{
				if (boss->PerformRaycast_Block(Vector, boss).hit)
				{//�u���b�N�ɓ������Ă�����
					if (boss->PerformRaycast_Block(Vector, boss).distance > boss->PerformRaycast_Player(Vector, boss).distance)
					{//�u���b�N����O�ɂ���Ƃ���
						boss->ChangeState(new CChaseState);
					}
				}
				else if (!boss->PerformRaycast_Block(Vector, boss).hit)
				{
					boss->ChangeState(new CChaseState);
				}
			}
		}
	}
}

//=============================================
//�{�X�̜p�j��ԃf�o�b�O
//=============================================
void CWanderingState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n�p�j");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CTackleState::CTackleState()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTackleState::~CTackleState()
{
	
}

//=============================================
//�ŏ��̈�񂾂��Ă΂��֐�
//=============================================
void CTackleState::Start(CBossEnemy* boss)
{

}

//=============================================
//�Ō�̈�񂾂��Ă΂��֐�
//=============================================
void CTackleState::End(CBossEnemy* boss)
{
	if (boss->m_pDashEffect != nullptr)
	{
		boss->m_pDashEffect->Uninit();
		boss->m_pDashEffect = nullptr;
	}
	if (boss->m_pTackleCharge != nullptr)
	{
		boss->m_pTackleCharge->Uninit();
		boss->m_pTackleCharge = nullptr;
	}
}

//=============================================
//�{�X�̃^�b�N������
//=============================================
void CTackleState::Tackle(CBossEnemy* boss)
{
	if (boss->m_pTackle != nullptr)
	{
		boss->m_pTackle->Tackle(boss);
	}
}

//=============================================
//�{�X�̃^�b�N����ԃf�o�b�O
//=============================================
void CTackleState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n�ːi");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�R���X�g���N�^
//=============================================
CConfusionBossState::CConfusionBossState()
{
	m_pReaction = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CConfusionBossState::~CConfusionBossState()
{
	if (m_pReaction != nullptr)
	{
		m_pReaction->Uninit();
		m_pReaction = nullptr;
	}
}

//=============================================
//�ŏ��ɌĂ΂��֐�
//=============================================
void CConfusionBossState::Start(CBossEnemy* boss)
{
	if (m_pReaction == nullptr)
	{
		m_pReaction = CEnemy_Reaction_UI::Create({ boss->m_apModel[1]->GetMtxWorld()._41,
			boss->m_apModel[1]->GetMtxWorld()._42 + 70.0f,
			boss->m_apModel[1]->GetMtxWorld()._43 }, { 40.0f,40.0f,0.0f }, CEnemy_Reaction_UI::REACTION::REACTION_CONFUSION);
	}

	m_StartRot = boss->GetRot().y;
	if (m_StartRot < D3DX_PI * 0.5f && m_StartRot > -D3DX_PI * 0.5f)
	{
		m_isRight = false;
	}
	else if (m_StartRot > D3DX_PI * 0.5f && m_StartRot < -D3DX_PI * 0.5f)
	{
		m_isRight = true;
	}
}

//=============================================
//�{�X�̍�������
//=============================================
void CConfusionBossState::Confusion(CBossEnemy* boss)
{
	if (boss->m_pConfusion != nullptr)
	{
		//�����̕������擾
		D3DXVECTOR3 vec = { sinf(boss->GetRot().y + D3DX_PI), 0.0f, cosf(boss->GetRot().y + D3DX_PI) };

		// ���C�L���X�g�����s���A��Q�������邩����
		if (boss->PerformRaycast_Player(vec, boss).hit)
		{
			if (boss->PerformRaycast_Block(vec, boss).hit)
			{//�u���b�N�ɓ������Ă�����
				if (boss->PerformRaycast_Block(vec, boss).distance > boss->PerformRaycast_Player(vec, boss).distance)
				{//�u���b�N����O�ɂ���Ƃ���
					boss->ChangeState(new CChaseState);
				}
			}
			else if (boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				if (boss->PerformRaycast_Smoke(vec, boss).distance > boss->PerformRaycast_Smoke(vec, boss).distance)
				{//�u���b�N����O�ɂ���Ƃ���
					boss->ChangeState(new CChaseState);
				}
			}
			else if (!boss->PerformRaycast_Block(vec, boss).hit && !boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				boss->ChangeState(new CChaseState);
			}
		}

		boss->m_pConfusion->Confusion(boss, m_StartRot);
	}

	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		boss->ChangeState(new CBossStanState);
	}
}

//=============================================
//�{�X�̍�����ԃf�o�b�O
//=============================================
void CConfusionBossState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n����");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�ŏ��̈�񂾂��Ă΂��֐�
//=============================================
void CSearchState::Start(CBossEnemy* boss)
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
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
				m_TargetPos = pPlayer->GetPos();
			}
		}
	}
}

//=============================================
//�v���C���[�T��
//=============================================
void CSearchState::Search(CBossEnemy* boss)
{
	if (boss->m_pSearch != nullptr)
	{
		boss->m_pSearch->Search(boss, m_TargetPos);
	}
}

//=============================================
//�{�X�̒T����ԃf�o�b�O
//=============================================
void CSearchState::DrawDebug()
{
}

//=============================================
//�ŏ��̈�񂾂��Ă΂��֐�
//=============================================
void CRampageState::Start(CBossEnemy* boss)
{
	boss->SetMove({ 0.0f,0.0f,0.0f });
}

//=============================================
//�Ō�̈�񂾂��Ă΂��֐�
//=============================================
void CRampageState::End(CBossEnemy* boss)
{
	if (boss->m_pDashEffect != nullptr)
	{
		boss->m_pDashEffect->Uninit();
		boss->m_pDashEffect = nullptr;
	}
}

//=============================================
//�{�X�̖\�����
//=============================================
void CRampageState::Rampage(CBossEnemy* boss)
{
	if (boss->m_pRampage != nullptr)
	{
		boss->m_pRampage->Rampage(boss);
	}
}

//=============================================
//�{�X�̖\����ԃf�o�b�O
//=============================================
void CRampageState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n�\��");
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
