//=============================================
//
//3DTemplate[object2D.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CObject2D::~CObject2D()
{
}

//=============================================
//������
//=============================================
HRESULT CObject2D::Init()
{
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CObject2D::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}


	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�������g�̉��
	Release();
}

//=============================================
//�X�V
//=============================================
void CObject2D::Update()
{
}

//=============================================
//�`��
//=============================================
void CObject2D::Draw()
{
 	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTexture);
	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

}

//=============================================
//���_�̐ݒ�
//=============================================
void CObject2D::SetVtx(float rhw, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y + m_size.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y + m_size.y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//�A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================
//���_�̐ݒ�(��]�A�g�k���܂�)
//=============================================
void CObject2D::SetVtx(float rhw, D3DCOLOR col, float fAngle, float fLength)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//�I�u�W�F�N�g�擾
	//	CObject* pObj = CObject::Getobject(4, nCnt);
	//	if (pObj != nullptr)
	//	{//�k���|�C���^����Ȃ����
	//		//�^�C�v�擾
	//		CObject::OBJECT_TYPE type = pObj->GetType();
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	//		{
	//			//���_���W�̐ݒ�
	//			pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				,0.0f);

	//			//���_���W�̐ݒ�
	//			pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, 0.0f);

	//			//���_���W�̐ݒ�
	//			pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y
	//				, 0.0f);

	//			//���_���W�̐ݒ�
	//			pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y
	//				, 0.0f);
	//		}
	//		else
	//		{

	//		}
	//	}
	//}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fLength
		, m_pos.y + cosf(m_rot.z - fAngle) * fLength
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fLength
		, m_pos.y + cosf(m_rot.z + fAngle) * fLength
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = rhw;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	//�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================
//���_�̐ݒ�(pos����)
//=============================================
void CObject2D::SetVtx_FootPos(float rhw, D3DCOLOR col, float fAngle, float fLength)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================
//�e�N�X�`���ݒ�
//=============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//=============================================
//���W�擾
//=============================================
D3DXVECTOR3& CObject2D::GetPos()
{
	return m_pos;
}

//=============================================
//�����擾
//=============================================
D3DXVECTOR3& CObject2D::GetRot()
{
	return m_rot;
}

//=============================================
//�T�C�Y�擾
//=============================================
D3DXVECTOR2& CObject2D::GetSize()
{
	return m_size;
}
//=============================================
//�e�N�X�`�����W�擾
//=============================================
D3DXVECTOR2& CObject2D::GetTexPos()
{
	return m_tex_pos;
}

//=============================================
//���_���擾
//=============================================
LPDIRECT3DVERTEXBUFFER9& CObject2D::GetVtxBuff()
{
	return m_pVtxBuff;
}

