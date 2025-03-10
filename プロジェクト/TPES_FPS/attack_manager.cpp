//=============================================
//
//�U���Ǘ��N���X[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "colision.h"
#include "player.h"
#include "model_parts.h"
#include "block.h"
#include "field.h"
#include"game.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),
m_nLife(INT_ZERO),					//�̗�
m_nDamage(INT_ZERO),				//�_���[�W
m_nNumkill(INT_ZERO)				//�L����
{
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

	if (m_nLife > INT_ZERO)
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
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
		{//�G�l�~�[����Ȃ����
			//�G�l�~�[��T��������
			continue;
		}

		//�G�Ƃ̓����蔻��
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		//�����蔻��m�F�ϐ��錾
		CColision::COLISION ColisionCheck;

		for (int nCntParts = 0; nCntParts < pEnemy->GetNumParts(); nCntParts++)
		{
			//�p�[�c�̃I�t�Z�b�gpos
			D3DXVECTOR3 PartsPos = { pEnemy->m_apModel[nCntParts]->GetMtxWorld()._41
			,pEnemy->m_apModel[nCntParts]->GetMtxWorld()._42
			,pEnemy->m_apModel[nCntParts]->GetMtxWorld()._43 };

			ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonModelColisionSphere(Attackpos, Attacksize, PartsPos, pEnemy->m_apModel[nCntParts]->GetMin(), pEnemy->m_apModel[nCntParts]->GetMax());

			if (ColisionCheck != CColision::COLISION::COLISON_NONE)
			{//�������Ă���
				if (nCntParts != 1)
				{//���ȊO�Ȃ�
					pEnemy->Damage(m_nDamage);
				}
				else if (nCntParts == 1)
				{//���Ȃ�
					//�_���[�W��{
					pEnemy->Damage(m_nDamage * 2);
				}

				//HIT����炷
				CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_HIT);

				return true;
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
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();


		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}

		//�v���C���[�Ƃ̓����蔻��
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		CColision::COLISION ColisionCheck;
		for (int nCnt = 0; nCnt < pPlayer->NUM_PARTS; nCnt++)
		{
			//�p�[�c�̃I�t�Z�b�gpos
			D3DXVECTOR3 PartsPos = { pPlayer->m_apModel[nCnt]->GetMtxWorld()._41
			,pPlayer->m_apModel[nCnt]->GetMtxWorld()._42
			,pPlayer->m_apModel[nCnt]->GetMtxWorld()._43 };

			ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonModelColisionSphere(Attackpos, Attacksize, PartsPos, pPlayer->m_apModel[nCnt]->GetMin(), pPlayer->m_apModel[nCnt]->GetMax());

			if (ColisionCheck != CColision::COLISION::COLISON_NONE)
			{//�������Ă���
				//�_���[�W�������Ă�
				pPlayer->Damage(m_nDamage);
				return true;
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

		//�u���b�N�Ƃ̓����蔻��
		CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

		CColision::COLISION ColisionCheck_X = CManager::GetInstance()->GetColision()->CheckPolygonModelColision_X(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
		CColision::COLISION ColisionCheck_Z = CManager::GetInstance()->GetColision()->CheckPolygonModelColision_Z(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

		if (ColisionCheck_X != CColision::COLISION::COLISON_NONE || ColisionCheck_Z != CColision::COLISION::COLISON_NONE)
		{//�������Ă���
			//�U���̍폜
			return true;
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
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		//�G�Ƃ̓����蔻��
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
		{//������Ȃ����
			//����T��������
			continue;
		}

		//���Ƃ̓����蔻��
		CField* pField = dynamic_cast<CField*>(pObj);

		CColision::COLISION ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonFillColision(Attackpos, Attacksize, pField->GetPos(),
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
	return false;
}