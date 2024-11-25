//=============================================
//
//3DTemplate[object3D.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "object3D.h"
#include "renderer.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CObject3D::CObject3D(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CObject3D::~CObject3D()
{
}

//=============================================
//������
//=============================================
HRESULT CObject3D::Init()
{
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CObject3D::Uninit()
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

	Release();
}

//=============================================
//�X�V
//=============================================
void CObject3D::Update()
{
}

//=============================================
//�`��
//=============================================
void CObject3D::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================
//�e�N�X�`���ݒ�
//=============================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//=============================================
//���_�̐ݒ�
//=============================================
void CObject3D::SetVtx(D3DXVECTOR3 nor, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x
		, m_size.y
		, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x
		, m_size.y
		, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x
		, -m_size.y
		, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x
		, -m_size.y
		, -m_size.z);


	//rhw�̐ݒ�
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	m_pVtxBuff->Unlock();

}


//=============================================
//���_�̐ݒ�(�g�k��])
//=============================================
void CObject3D::SetVtx(D3DXVECTOR3 nor, float fAngle, float fLength, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, m_size.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, m_size.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fLength
		, -m_size.y + cosf(m_rot.z - fAngle) * fLength
		, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fLength
		, -m_size.y + cosf(m_rot.z + fAngle) * fLength
		, -m_size.z);

	//rhw�̐ݒ�
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================
//�A�j���[�V������p���_�̐ݒ�
//=============================================
void CObject3D::SetVtxAnim(D3DXVECTOR3 nor, D3DCOLOR col,D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move)
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//���_���W�̐ݒ�
 	pVtx[0].pos = D3DXVECTOR3(-m_size.x
		, m_size.y
		, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x
		, m_size.y
		, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x
		, -m_size.y
		, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x
		, -m_size.y
		, -m_size.z);


	//rhw�̐ݒ�
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	m_nAnimCnt++;

	if (m_nAnimCnt >= m_nAnimFrame)
	{//�t���[�������B������
		//�e�N�X�`�������炷
 		tex_pos.x += tex_move.x;
		m_tex_move = tex_move;

		m_nAnimCnt = 0;
	}

	//�e�N�X�`���̍��W�w��
	pVtx[0].tex = D3DXVECTOR2(tex_pos.x
		, tex_pos.y);
	pVtx[1].tex = D3DXVECTOR2(tex_pos.x + tex_move.x
		, tex_pos.y);
	pVtx[2].tex = D3DXVECTOR2(tex_pos.x
		, tex_pos.y + tex_move.y);
	pVtx[3].tex = D3DXVECTOR2(tex_pos.x + tex_move.x
		, tex_pos.y + tex_move.y);

	SetTexPos(tex_pos);
	//�A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================
//���_�̐ݒ�(pos����)
//=============================================
void CObject3D::SetVtx_FootPos(D3DXVECTOR3 nor, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y + m_size.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y + m_size.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================
//���W�擾
//=============================================
D3DXVECTOR3& CObject3D::GetPos()
{
	return m_pos;
}

//=============================================
//�����擾
//=============================================
D3DXVECTOR3& CObject3D::GetRot()
{
	return m_rot;
}

//=============================================
//�T�C�Y�擾
//=============================================
D3DXVECTOR3& CObject3D::GetSize()
{
	return m_size;
}

//=============================================
//�e�N�X�`�����W�擾
//=============================================
D3DXVECTOR2& CObject3D::GetTexPos()
{
	return m_tex_pos;
}

//=============================================
//���_���擾
//=============================================
LPDIRECT3DVERTEXBUFFER9& CObject3D::GetVtxBuff()
{
	return m_pVtxBuff;
}

//=============================================
//�e�N�X�`�����擾
//=============================================
LPDIRECT3DTEXTURE9& CObject3D::GetTexture()
{
	return m_pTexture;
}

//=============================================
//���[���h�}�g���b�N�X�擾
//=============================================
D3DXMATRIX& CObject3D::GetMtxWorld()
{
	return m_mtxWorld;
}

//=============================================
//�A�j���[�V�����t���[�����擾
//=============================================
int CObject3D::GetAnimFrame()
{
	return m_nAnimFrame;
}

//=============================================
//�e�N�X�`���̃��[�u�ʎ擾
//=============================================
D3DXVECTOR2& CObject3D::GetTexMove()
{
	return m_tex_move;
}
