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
const char* CBlock::MODEL_NAME = "data\\MODEL\\c.x";

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

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// ��r�Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// �X�e���V���}�X�N���w�肷��
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// �X�e���V����r�֐����w�肷��
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// �X�e���V�����ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// Z�e�X�g�E�X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g�E�X�e���V���e�X�g���s
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g���s�E�X�e���V���e�X�g����

	//�e�N���X�̕`�揈��
	CObjectX::Draw();

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================
//�u���b�N����
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;

	//null�Ȃ�null��Ԃ�
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetInstance()->GetModel();
	CTexture* pTex = CManager::GetInstance()->GetTexture();

	pBlock->m_type = type;
	pBlock->SetPos(pos); //pos�ݒ�
	pBlock->SetRot(rot); //pos�ݒ�
	pBlock->m_nLife = nLife; //�������
	pBlock->m_bBreak = bBreak; //�󂹂邩�ǂ���
	//pBlock->BindTexture(m_pTextureTemp);

	//X�t�@�C���ǂݍ���
	pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pBlock->SetType(OBJECT_TYPE_BLOCK); //�^�C�v�ݒ�
	pBlock->Init();
	
	return pBlock;
}