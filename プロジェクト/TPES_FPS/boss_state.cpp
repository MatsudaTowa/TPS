//=============================================
//
//�{�X�̃X�e�[�g�p�^�[��[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player_test.h"

//=============================================
//�{�X�̒ǐՏ��(���ł͉������Ȃ�)
//=============================================
void CBossState::Chase(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̜p�j���(���ł͉������Ȃ�)
//=============================================
void CBossState::Wandering(CBossEnemy* boss)
{
}

//=============================================
//�{�X�̃^�b�N�����(���ł͉������Ȃ�)
//=============================================
void CBossState::Tackle(CBossEnemy* boss)
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
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
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
	if (boss->GetLife() < HP_LOW)
	{//HP���Ⴂ��Ԃ�������

		boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);

		++m_PlayTackleCnt;

		if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
		{//�^�b�N�����s�t���[���ɓ��B������
			m_PlayTackleCnt = 0;
			//�X�e�[�g�؂�ւ�
			boss->ChangeState(new CTackleState);
		}
	}
	else if (boss->GetLife() >= HP_LOW)
	{
		boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);
	}

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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//�{�X�̜p�j���
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
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
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				//�v���C���[�̈ʒu�ւ̕������
				D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

				// �ړI�n�Ƃ̋������v�Z
				float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

				if (distance < boss->FIND_PLAYER_DISTANCE)
				{//�߂�������
					boss->ChangeState(new CChaseState); //�ǐՏ�ԂɕύX
				}
				else if (boss->m_pWandering != nullptr)
				{
					boss->m_pWandering->Wandering(boss);
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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
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
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
