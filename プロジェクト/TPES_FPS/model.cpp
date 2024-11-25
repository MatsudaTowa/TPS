//=============================================
//
//3DTemplate[model.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "model.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CModel::CModel()
{
	//���f����񏉊���
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_ModelInfo[nCnt].pBuffMat = nullptr;
		m_ModelInfo[nCnt].pMesh = nullptr;
		m_ModelInfo[nCnt].dwNumMat = 0;
	}

	m_nNumAll = 0;
}

//=============================================
//�f�X�g���N�^
//=============================================
CModel::~CModel()
{
}

//=============================================
//���f���j��
//=============================================
void CModel::Unload()
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
//���f���o�^
//=============================================
int CModel::Regist(const char* pModel)
{
	int nIdx = 0;
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_ModelInfo[nCnt].pBuffMat == nullptr
			&& m_ModelInfo[nCnt].pMesh == nullptr)
		{
			LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(pModel,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_ModelInfo[nCnt].pBuffMat,
				NULL,
				&m_ModelInfo[nCnt].dwNumMat,
				&m_ModelInfo[nCnt].pMesh);

			//�����̃t�@�C���p�X��ۑ�
			m_ModelInfo[nCnt].ModelName = pModel;
			nIdx = nCnt;	//�ԍ��̕ۑ�
			m_nNumAll++;	//�����̃J�E���g�A�b�v
			break;
		}
		if (strcmp(m_ModelInfo[nCnt].ModelName, pModel) == 0)
		{//�����̃��f�������݂���Ȃ�
		
			//�ԍ���������break
			nIdx = nCnt;
			break;
		}
	}
	return nIdx;
}

//=============================================
//���f�����擾
//=============================================
CModel::MODEL_INFO CModel::GetModelInfo(int nIdx)
{
	return m_ModelInfo[nIdx];
}

