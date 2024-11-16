//=============================================
// 
//�e�q�֌W�̃p�[�c[model.h]
//Auther Matsuda Towa
//
//=============================================
#include "model_parts.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CModel_Parts::CModel_Parts()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CModel_Parts::~CModel_Parts()
{
}

//=============================================
//�폜
//=============================================
void CModel_Parts::Unload()
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_ModelInfo[nCnt].pBuffMat != nullptr)
		{//�}�e���A���j��
			m_ModelInfo[nCnt].pBuffMat->Release();
			m_ModelInfo[nCnt].pBuffMat = nullptr;
			m_ModelInfo[nCnt].dwNumMat = 0;
		}
		if (m_ModelInfo[nCnt].pMesh != nullptr)
		{//���b�V���j��
			m_ModelInfo[nCnt].pMesh->Release();
			m_ModelInfo[nCnt].pMesh = nullptr;
		}

		if (m_ModelInfo[nCnt].ModelName != nullptr)
		{//���f���l�[���j��
			m_ModelInfo[nCnt].ModelName = nullptr;
		}
	}
	m_nNumAll = 0;
}

//=============================================
//���f���ݒ�
//=============================================
void CModel_Parts::BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh)
{

	pBuffMat->AddRef();
	pMesh->AddRef();

	m_ModelInfo->pBuffMat = pBuffMat;
	m_ModelInfo->dwNumMat = dwNumMat;
	m_ModelInfo->pMesh = pMesh;

	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

		//���_���̎擾
	nNumVtx = m_ModelInfo->pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_ModelInfo->pMesh->GetFVF());

	m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
	m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

	//���_�o�b�t�@�̃��b�N
	m_ModelInfo->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
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

	m_ModelInfo->pMesh->UnlockVertexBuffer();
}

//=============================================
//�`��
//=============================================
void CModel_Parts::Draw()
{
	if (m_ModelInfo->pMesh != nullptr && m_ModelInfo->pBuffMat != nullptr)
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

		D3DXMATRIX mtxParent; //�e�̍s��擾

		if (m_pParent != nullptr)
		{
			//�e�̃��[���h�}�g���b�N�X�擾
			mtxParent = m_pParent->GetMtxWorld();
		}
		else
		{
			//�ŐV�̃��[���h�Ԋҍs����擾
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //�}�e���A��

		pMat = (D3DXMATERIAL*)m_ModelInfo->pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_ModelInfo->dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//�p�[�c�̐ݒ�
			m_ModelInfo->pMesh->DrawSubset(nCntMat);
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
//�`��(material�̐F�ύX)
//=============================================
void CModel_Parts::Draw(D3DXCOLOR col)
{
	if (m_ModelInfo->pMesh != nullptr && m_ModelInfo->pBuffMat != nullptr)
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

		D3DXMATRIX mtxParent; //�e�̍s��擾

		if (m_pParent != nullptr)
		{
			//�e�̃��[���h�}�g���b�N�X�擾
			mtxParent = m_pParent->GetMtxWorld();
		}
		else
		{
			//�ŐV�̃��[���h�Ԋҍs����擾
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //�}�e���A��

		pMat = (D3DXMATERIAL*)m_ModelInfo->pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_ModelInfo->dwNumMat; nCntMat++)
		{
			//���`�悷��}�e���A�����i�[
			D3DMATERIAL9 DrawMat = pMat[nCntMat].MatD3D;

			DrawMat.Diffuse = col;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&DrawMat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//�p�[�c�̐ݒ�
			m_ModelInfo->pMesh->DrawSubset(nCntMat);
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
//����
//=============================================
CModel_Parts* CModel_Parts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,char* pModel_Path)
{
	CModel_Parts*pModelParts = new CModel_Parts;
	CModel* pModel = CManager::GetModel();
	if (pModelParts == nullptr)
	{
		return nullptr;
	}

	pModelParts->m_pos = pos; //���_���
	pModelParts->m_rot = rot; //���_���

	//X�t�@�C���ǂݍ���
	pModelParts->BindXFile(pModel->GetModelInfo(pModel->Regist(pModel_Path)).pBuffMat, //�}�e���A���擾
		pModel->GetModelInfo(pModel->Regist(pModel_Path)).dwNumMat, //�}�e���A�����擾
		pModel->GetModelInfo(pModel->Regist(pModel_Path)).pMesh); //���b�V�����擾

	return pModelParts;
}

//=============================================
//�e�p�[�c�̐ݒ�
//=============================================
void CModel_Parts::SetParent(CModel_Parts* pParent)
{
	m_pParent = pParent;
}

D3DXMATRIX& CModel_Parts::GetMtxWorld()
{
	return m_mtxWorld;
}

CModel_Parts::MODEL_INFO CModel_Parts::GetModelInfo(int nIdx)
{
	return m_ModelInfo[nIdx];
}

