//=============================================
//
//�E���g�͈͏���[ult_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_range.h"
#include "manager.h"
#include "enemy.h"
#include "object.h"

//=============================================
//�R���X�g���N�^
//=============================================
CUltRange::CUltRange() :m_nLife(INT_ZERO), m_pos(VEC3_RESET_ZERO), m_pUltEffect(nullptr)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CUltRange::~CUltRange()
{
}

//=============================================
//������
//=============================================
HRESULT CUltRange::Init()
{
	m_nLife = LIFE;

	if (m_pUltEffect == nullptr)
	{
		m_pUltEffect = CUltEffect::Create({ m_pos.x, 0.5f, m_pos.z }, VEC3_RESET_ZERO);
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CUltRange::Uninit()
{
	if (m_pUltEffect != nullptr)
	{
		m_pUltEffect->Uninit();
		m_pUltEffect = nullptr;
	}
	delete this;
}

//=============================================
//�X�V
//=============================================
void CUltRange::Update()
{
	//���łɑ̗͂��Ȃ��Ȃ�֐��𔲂���
	if (m_nLife <= INT_ZERO)
	{
		return;
	}

	--m_nLife;

	if (m_pUltEffect != nullptr)
	{
		D3DXVECTOR3 size = m_pUltEffect->GetSize();

		size.x += 20.0f;
		size.z += 20.0f;

		m_pUltEffect->SetSize(size);
	}

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ��΂�
			continue;
		}

		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		//�G�Ƃ̓����蔻��
		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
		{
			CEnemy* enemy = dynamic_cast<CEnemy*>(pObj);

			CColision::CIRCLE ColisionCheck;

			ColisionCheck = CManager::GetInstance()->GetColision()->CheckColisionCircle(m_pos, RADIUS, enemy->GetPos());

			if (ColisionCheck.colision != CColision::COLISION::COLISON_NONE)
			{
				if (ColisionCheck.CenterDistance < (RADIUS * RADIUS) * HALF)
				{//�߂�������}�b�N�X�_���[�W
					enemy->MediumUltHit(m_pos, MAX_DAMAGE);
				}
				else
				{
					enemy->MediumUltHit(m_pos, MAX_DAMAGE * HALF);
				}
			}
		}
	}
}

//=============================================
//����
//=============================================
CUltRange* CUltRange::Create(D3DXVECTOR3 pos)
{
	CUltRange* pRange = new CUltRange;

	//���������ĂȂ�������return
	if (pRange == nullptr) { return nullptr; }

	pRange->m_pos = pos;
	pRange->Init();

	return pRange;
}
