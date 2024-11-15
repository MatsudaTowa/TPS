//=============================================
//
//3DTemplate[objectX.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
//=============================================
//�R���X�g���N�^
//=============================================
CObjectX::CObjectX(int nPriority):CObject(nPriority),m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
{
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_pTexture[nCnt] = nullptr;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CObjectX::~CObjectX()
{
}

//=============================================
//������
//=============================================
HRESULT CObjectX::Init()
{

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CObjectX::Uninit()
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	Release();

}

//=============================================
//�X�V
//=============================================
void CObjectX::Update()
{
}

//=============================================
//�`��
//=============================================
void CObjectX::Draw()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		//�f�o�C�X�̎擾
		CRenderer* pRender = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
		D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
		D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

		//�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //�}�e���A��

		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//�p�[�c�̐ݒ�
			m_pMesh->DrawSubset(nCntMat);
		}

		// �f�B�t���[�Y�J���[��ύX
		pMat->MatD3D.Diffuse = D3DXCOLOR(pMat->MatD3D.Diffuse.r, pMat->MatD3D.Diffuse.g, pMat->MatD3D.Diffuse.b, pMat->MatD3D.Diffuse.a);

		//���e�X�g�𖳌���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//���݂��擾
		pDevice->GetMaterial(&matDef);

		//�ۑ����Ă��}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
	
}

//=============================================
//�`��(�J���[�ύX)
//=============================================
void CObjectX::Draw(D3DXCOLOR col)
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		//�f�o�C�X�̎擾
		CRenderer* pRender = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
		D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
		D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

		//�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //�}�e���A��

		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			//���`�悷��}�e���A�����i�[
			D3DMATERIAL9 DrawMat = pMat[nCntMat].MatD3D;

			DrawMat.Diffuse = col;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&DrawMat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//�p�[�c�̐ݒ�
			m_pMesh->DrawSubset(nCntMat);

		}

		//���e�X�g�𖳌���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//���݂��擾
		pDevice->GetMaterial(&matDef);

		//�ۑ����Ă��}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

}

//=============================================
//�e�N�X�`���ݒ�
//=============================================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = pTex;
	}
}

//=============================================
//���f���ݒ�
//=============================================
void CObjectX::BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh)
{
	pBuffMat->AddRef();
	pMesh->AddRef();

	m_pBuffMat = pBuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = pMesh;

	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

		//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
	m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.x > m_maxpos.x)
		{
			m_maxpos.x = vtx.x;
		}
		if (vtx.x < m_minpos.x)
		{
			m_minpos.x = vtx.x;
		}

		//y���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.y > m_maxpos.y)
		{
			m_maxpos.y = vtx.y;
		}
		if (vtx.y < m_minpos.y)
		{
			m_minpos.y = vtx.y;
		}

		//z���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.z > m_maxpos.z)
		{
			m_maxpos.z = vtx.z;
		}
		if (vtx.z < m_minpos.z)
		{
			m_minpos.z = vtx.z;
		}

		// ���̒��_�ɐi��
		pVtxBuff += sizeFVF;
	}

	m_pMesh->UnlockVertexBuffer();
}

//=============================================
//���W�擾
//=============================================
D3DXVECTOR3& CObjectX::GetPos()
{
	return m_pos;
}

//=============================================
//�����擾
//=============================================
D3DXVECTOR3& CObjectX::GetRot()
{
	return m_rot;
}

//=============================================
//�ŏ��l�擾
//=============================================
D3DXVECTOR3& CObjectX::GetMinPos()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		int nNumVtx; //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

			//���_���̎擾
		nNumVtx = m_pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
		m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

		//���_�o�b�t�@�̃��b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x���W�̍ŏ��l�`�F�b�N
			if (vtx.x < m_minpos.x)
			{
				m_minpos.x = vtx.x;
			}

			//y���W�̍ŏ��l�`�F�b�N
			if (vtx.y < m_minpos.y)
			{
				m_minpos.y = vtx.y;
			}

			//z���W�̍ŏ��l�`�F�b�N
			if (vtx.z < m_minpos.z)
			{
				m_minpos.z = vtx.z;
			}

			// ���̒��_�ɐi��
			pVtxBuff += sizeFVF;
		}

		m_pMesh->UnlockVertexBuffer();
	}
	
	return m_minpos;
}

//=============================================
//�ő�l�擾
//=============================================
D3DXVECTOR3& CObjectX::GetMaxPos()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		int nNumVtx; //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

			//���_���̎擾
		nNumVtx = m_pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
		m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

	//���_�o�b�t�@�̃��b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x���W�̍ő�l�`�F�b�N
			if (vtx.x > m_maxpos.x)
			{
				m_maxpos.x = vtx.x;
			}

			//y���W�̍ő�l�`�F�b�N
			if (vtx.y > m_maxpos.y)
			{
				m_maxpos.y = vtx.y;
			}

			//z���W�̍ő�l�`�F�b�N
			if (vtx.z > m_maxpos.z)
			{
				m_maxpos.z = vtx.z;
			}
			// ���̒��_�ɐi��
			pVtxBuff += sizeFVF;
		}

		m_pMesh->UnlockVertexBuffer();
	}
	
	return m_maxpos;
}

//=============================================
//���b�V�����擾
//=============================================
LPD3DXMESH& CObjectX::GetpMesh()
{
	return m_pMesh;
}

//=============================================
//�}�e���A�����擾
//=============================================
LPD3DXBUFFER& CObjectX::GetpBuffMat()
{
	return m_pBuffMat;
}

//=============================================
//�}�e���A�����擾
//=============================================
DWORD& CObjectX::GetNumMat()
{
	return m_dwNumMat;
}

//=============================================
//���[���h�}�g���b�N�X�擾
//=============================================
D3DXMATRIX& CObjectX::GetMtxWorld()
{
	return m_mtxWorld;
}

//=============================================
//�J���[�擾
//=============================================
D3DXCOLOR& CObjectX::GetCol()
{
	return m_col;
}
