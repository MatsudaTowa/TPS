//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"

//���f���p�X
const std::string CBlock::MODEL_NAME = "data\\MODEL\\Container.x";
const std::string CBlock::WOOD_MODEL_NAME = "data\\MODEL\\wood.x";
const std::string CBlock::AZUMAYA_MODEL_NAME = "data\\MODEL\\azumaya.x";
const std::string CBlock::DANGOYA_MODEL_NAME = "data\\MODEL\\dangoya.x";
const std::string CBlock::MESH_MODEL_NAME = "data\\MODEL\\mesh.x";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;

LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;

LPD3DXMESH CBlock::m_pMesh = nullptr;

DWORD CBlock::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//������
//=============================================
HRESULT CBlock::Init()
{
	//�e�N���X�̏���������
	CObjectX::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlock::Uninit()
{
	//�e�N���X�̏I������
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBlock::Update()
{
	//�e�N���X�̍X�V����
	CObjectX::Update();
}

//=============================================
//�`��
//=============================================
void CBlock::Draw()
{
	//�e�N���X�̕`�揈��
	CObjectX::Draw();
}

//=============================================
//�u���b�N����
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;

	//null�Ȃ�null��Ԃ�
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetModel();
	CTexture* pTex = CManager::GetTexture();

	pBlock->m_type = type;
	pBlock->SetPos(pos); //pos�ݒ�
	pBlock->SetRot(rot); //pos�ݒ�
	pBlock->m_nLife = nLife; //�������
	pBlock->m_bBreak = bBreak; //�󂹂邩�ǂ���
	//pBlock->BindTexture(m_pTextureTemp);

	switch (pBlock->m_type)
	{
	case CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT:
		//X�t�@�C���ǂݍ���
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);
			break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_WOOD:
		//X�t�@�C���ǂݍ���
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_AZUMAYA:
		//X�t�@�C���ǂݍ���
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_DANGOYA:
		//X�t�@�C���ǂݍ���
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_MESH:
		//X�t�@�C���ǂݍ���
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).pMesh);
		D3DXMATERIAL* pMat; //�}�e���A��
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		//pBlock->BindTexture((pTex->GetAddress(pTex->Regist(&pMat->pTextureFilename()))); //�e�N�X�`���ݒ�
		break;
	default:
		break;
	}

	pBlock->SetType(OBJECT_TYPE_BLOCK); //�^�C�v�ݒ�
	pBlock->Init();
	
	return pBlock;
}