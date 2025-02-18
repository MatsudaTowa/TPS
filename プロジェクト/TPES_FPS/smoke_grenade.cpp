//=============================================
//
//�X���[�N�O���l�[�h����[somoke_grenade.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_grenade.h"
#include "manager.h"
#include "smoke_range.h"
#include "field.h"

//���f���p�X
const char* CSmokeGrenade::MODEL_NAME = "data\\MODEL\\jett.x";

//=============================================
//�R���X�g���N�^
//=============================================
CSmokeGrenade::CSmokeGrenade(int nPriority) : CObjectX(nPriority),m_move(VEC3_RESET_ZERO), m_oldpos(VEC3_RESET_ZERO), m_bBoot(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmokeGrenade::~CSmokeGrenade()
{
}

//=============================================
//������
//=============================================
HRESULT CSmokeGrenade::Init()
{
	m_bBoot = false;
	CObjectX::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmokeGrenade::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmokeGrenade::Update()
{
	CObjectX::Update();

	D3DXVECTOR3 pos = GetPos();

	m_oldpos = pos;

	pos += m_move;

	SetPos(pos);

	//���Ƃ̔���
	HitField();

	if (m_bBoot)
	{//�y�􂵂���
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SMOKE);

		for (int nCnt = INT_ZERO; nCnt < CREATE_SMOKE_NUM; nCnt++)
		{
			CSmoke::Create(GetPos(),CSmoke::SMOKE_TYPE_TACTICAL);
		}
		CSmokeRange::Create(GetPos(), VEC3_RESET_ZERO);
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CSmokeGrenade::Draw()
{
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CSmokeGrenade* CSmokeGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	CSmokeGrenade* pSmokeGrenade = new CSmokeGrenade;

	if (pSmokeGrenade == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	//X�t�@�C���ǂݍ���
	pSmokeGrenade->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pSmokeGrenade->SetPos(pos);
	pSmokeGrenade->m_move = move;
	pSmokeGrenade->SetRot(rot);
	pSmokeGrenade->Init();
	pSmokeGrenade->SetType(OBJECT_TYPE_SMOKE_GRENADE);

	return pSmokeGrenade;
}

//=============================================
//���Ƃ̔���
//=============================================
void CSmokeGrenade::HitField()
{
	D3DXVECTOR3 pos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 min = GetMinPos();
	D3DXVECTOR3 max = GetMaxPos();

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
				CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, pos, min, max, pField->GetPos(), pField->GetSize());

				if (colision == CColision::COLISION::COLISON_TOP_Y)
				{//y(��)�����ɓ������Ă���
					pos.y = m_oldpos.y;
					m_move = VEC3_RESET_ZERO;
					m_bBoot = true;
				}

				//TODO:�ǂ̓����蔻�������炱����g���K�v�Ȃ��Ȃ�
				{
					if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
						&& pos.x < pField->GetPos().x - pField->GetSize().x)
					{
						pos.x = m_oldpos.x;
						m_move = VEC3_RESET_ZERO;
						m_bBoot = true;
					}

					if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
						&& pos.x > pField->GetPos().x + pField->GetSize().x)
					{
						pos.x = m_oldpos.x;
						m_move = VEC3_RESET_ZERO;
						m_bBoot = true;
					}

					if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z
						&& pos.z < pField->GetPos().z - pField->GetSize().z)
					{
						pos.z = m_oldpos.z;
						m_move = VEC3_RESET_ZERO;
						m_bBoot = true;
					}

					if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z
						&& pos.z > pField->GetPos().z + pField->GetSize().z)
					{
						pos.z = m_oldpos.z;
						m_move = VEC3_RESET_ZERO;
						m_bBoot = true;
					}
				}
			}
		}
	}
	SetPos(pos);

}
