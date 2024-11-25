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
