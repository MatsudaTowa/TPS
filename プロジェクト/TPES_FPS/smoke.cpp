//=============================================
//
//�X���[�N����[somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke.h"
#include "smoke_range.h"
#include "manager.h"

const std::string CSmoke::SMOKE_TEXTURE_NAME = "data\\TEXTURE\\effect000.jpg";

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

		//TODO:�����蔻���colision�ɂ܂Ƃ߂�
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
		CObject* pObj = CObject::Getobject(CSmokeRange::SMOKE_RANGE_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
		 //�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_SMOKE_RANGE)
			{
				CSmokeRange* pRange = dynamic_cast<CSmokeRange*>(pObj);

				if (GetPos().x - GetSize().x < pRange->GetPos().x + pRange->GetMinPos().x)
				{
					m_move.x += 0.01f;
				}
				else if (GetPos().x + GetSize().x > pRange->GetPos().x + pRange->GetMaxPos().x)
				{
					m_move.x -= 0.01f;
				}

				if (GetPos().z< pRange->GetPos().z + pRange->GetMinPos().z)
				{
					m_move.z += 0.01f;
				}
				else if (GetPos().z > pRange->GetPos().z + pRange->GetMaxPos().z)
				{
					m_move.z -= 0.01f;
				}

				if (GetPos().y < pRange->GetPos().y + pRange->GetMinPos().y)
				{
					m_move.y += 0.01f;
				}
				else if (GetPos().y > pRange->GetPos().y + pRange->GetMaxPos().y)
				{
					m_move.y -= 0.01f;
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
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�r���{�[�h�̕`�揈��
	CBillboard::Draw();

	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pSmoke->BindTexture(pTexture->GetAddress(pTexture->Regist(&SMOKE_TEXTURE_NAME)));

	return pSmoke;
}
