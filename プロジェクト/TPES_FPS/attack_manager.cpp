//=============================================
//
//�U���Ǘ��N���X[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "colision.h"
#include "player.h"
#include "enemy_test.h"
#include "model_parts.h"
#include "block.h"
#include "field.h"
#include"game.h"
#include "player_test.h"
//=============================================
//�R���X�g���N�^
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),m_nLife(0),m_nDamage(0),m_nNumkill(0)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�̗͂ƃ_���[�W������
}

//=============================================
//�f�X�g���N�^
//=============================================
CAttack_Manager::~CAttack_Manager()
{
}

//=============================================
//������
//=============================================
HRESULT CAttack_Manager::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAttack_Manager::Uninit()
{
	//�e�N���X�̏I������
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CAttack_Manager::Update()
{
	//�e�N���X�̍X�V����
	CObject3D::Update();

	if (m_nLife > 0)
	{//����������Ȃ猸�炷
		m_nLife--;
	}
}

//=============================================
//�`��
//=============================================
void CAttack_Manager::Draw()
{
	//�e�N���X�̕`�揈��
	CBillboard::Draw();
}

//=============================================
//�U�������蔻��(�G�l�~�[)
//=============================================
bool CAttack_Manager::HitEnemy()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

				CColision::COLISION ColisionCheck;
				for (int nCnt = 0; nCnt < pEnemy->NUM_PARTS; nCnt++)
				{
					//�p�[�c�̃I�t�Z�b�gpos
					D3DXVECTOR3 PartsPos = { pEnemy->m_apModel[nCnt]->GetMtxWorld()._41
					,pEnemy->m_apModel[nCnt]->GetMtxWorld()._42
					,pEnemy->m_apModel[nCnt]->GetMtxWorld()._43 };

					ColisionCheck = CColision::CheckPolygonModelColisionCircle(Attackpos, Attacksize, PartsPos, pEnemy->m_apModel[nCnt]->m_minpos, pEnemy->m_apModel[nCnt]->m_maxpos);

					if (ColisionCheck != CColision::COLISION::COLISON_NONE)
					{//�������Ă���
						pEnemy->Damage(m_nDamage);
						int nCurrentLife = pEnemy->GetLife();
						return true;
					}
				}
			}
		}
	}
	return false;
}

//=============================================
//�U�������蔻��(�v���C���[)
//=============================================
bool CAttack_Manager::HitPlayer()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
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
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				CColision::COLISION ColisionCheck;
				for (int nCnt = 0; nCnt < pPlayer_test->NUM_PARTS; nCnt++)
				{
					//�p�[�c�̃I�t�Z�b�gpos
					D3DXVECTOR3 PartsPos = { pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._41
					,pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._42
					,pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._43 };

					ColisionCheck = CColision::CheckPolygonModelColisionCircle(Attackpos, Attacksize, PartsPos, pPlayer_test->m_apModel[nCnt]->m_minpos, pPlayer_test->m_apModel[nCnt]->m_maxpos);

					if (ColisionCheck != CColision::COLISION::COLISON_NONE)
					{//�������Ă���
						pPlayer_test->Damage(m_nDamage);
						int nCurrentLife = pPlayer_test->GetLife();
						return true;
					}
				}
			}
		}
	}
}

//=============================================
//�U�������蔻��(�u���b�N)
//=============================================
bool CAttack_Manager::HitBlock()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
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

				CColision::COLISION ColisionCheck_X = CColision::CheckPolygonModelColision_X(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
				CColision::COLISION ColisionCheck_Z = CColision::CheckPolygonModelColision_Z(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				if (ColisionCheck_X != CColision::COLISION::COLISON_NONE || ColisionCheck_Z != CColision::COLISION::COLISON_NONE)
				{//�������Ă���
					//�U���̍폜
					return true;
				}
			}
		}
	}
	return false;
}

//=============================================
//�U�������蔻��(��)
//=============================================
bool CAttack_Manager::HitGround()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = dynamic_cast<CField*>(pObj);

				CColision::COLISION ColisionCheck = CColision::CheckItemFillColision(Attackpos, Attacksize, pField->GetPos(),
				D3DXVECTOR3(-pField->GetSize().x, -pField->GetSize().y, -pField->GetSize().z), 
				D3DXVECTOR3(pField->GetSize().x, pField->GetSize().y, pField->GetSize().z));

				if (ColisionCheck == CColision::COLISION::COLISON_TOP_Y)
				{//�������Ă���
					//���܂��Ă镪�𑫂�
					Attackpos.y += pField->GetPos().y - (Attackpos.y - Attacksize.y);

					SetPos(Attackpos);
					return true;

				}
				else
				{
					return false;
				}
				break;
			}
		}
	}

}

//=============================================
//�̗͎擾
//=============================================
int CAttack_Manager::GetLife()
{
	return m_nLife;
}

//=============================================
//�_���[�W�擾
//=============================================
int CAttack_Manager::GetDamage()
{
	return m_nDamage;
}
