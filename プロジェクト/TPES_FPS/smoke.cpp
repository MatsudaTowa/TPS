//=============================================
//
//�X���[�N����[somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke.h"
#include "smoke_range.h"

//=============================================
//�R���X�g���N�^
//=============================================
CSmoke::CSmoke(int nPriority) : CBillboard(nPriority),m_nLife(0),m_move({0.0f,0.0f,0.0f}), m_oldpos({ 0.0f,0.0f,0.0f })
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmoke::~CSmoke()
{
}

//=============================================
//������
//=============================================
HRESULT CSmoke::Init()
{
	CObject3D::Init();
	m_nLife = SMOKE_LIFE; //���C�t�ݒ�
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmoke::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmoke::Update()
{
	CObject3D::Update();

	if (m_nLife > 0)
	{
		--m_nLife;
		D3DXVECTOR3 pos = GetPos();

		m_oldpos = pos;

		pos += m_move;

		SetPos(pos);

		ColisionRange();
	}
	else
	{
		Uninit();
	}
}

//=============================================
//�X���[�N�����蔻��
//=============================================
void CSmoke::ColisionRange()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CSmokeRange::SMOKE_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
		 //�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_SMOKE_RANGE)
			{
				CSmokeRange* pRange = dynamic_cast<CSmokeRange*>(pObj);

				if (GetPos().x < pRange->GetMinPos().x)
				{
					m_move.x += 0.01f;
				}
				if (GetPos().x > pRange->GetMaxPos().x)
				{
					m_move.x -= 0.01f;
				}
			}
		}
	}
}

//=============================================
//�`��
//=============================================
void CSmoke::Draw()
{
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CSmoke* pSmoke = new CSmoke;

	if(pSmoke == nullptr) {return nullptr;}

	pSmoke->SetPos(pos);
	pSmoke->m_move = move;
	pSmoke->SetRot(rot);
	pSmoke->SetSize(size);
	pSmoke->Init();
	pSmoke->SetType(OBJECT_TYPE_SMOKE);

	return pSmoke;
}
