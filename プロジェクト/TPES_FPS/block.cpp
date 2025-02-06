//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"
#include "block_piece.h"
#include "smoke.h"
#include "smoke_range.h"

//���f���p�X
const char* CBlock::MODEL_NAME = "data\\MODEL\\Container000.x";

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

#ifdef _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		CreatePiece();
		Uninit();
	}
#endif // _DEBUG
}

//=============================================
//�u���b�N�̔j�А���
//=============================================
void CBlock::CreatePiece()
{
	//�����SE��炷
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BREAK);

	for (int nCnt = 0; nCnt < NUM_SMOKE; nCnt++)
	{
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_int_distribution<int> number_x(-3, 3);
		std::uniform_int_distribution<int> number_y(0, 5);
		std::uniform_int_distribution<int> number_z(0, 1);
		CSmoke::Create({ GetPos().x,10.0f,GetPos().z }, { number_x(random) * 0.1f,number_y(random) * 0.1f,number_z(random) * 0.1f }, { 0.0f,0.0f,0.0f }, { 30.0f,30.0f,0.0f }, {0.1f,0.1f,0.1f,1.0f});
	}

	for (int nNumCreate = 0; nNumCreate < NUM_PIECE; ++nNumCreate)
	{
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_int_distribution<int> rot(0, 3);
		CBlock_Piece::Create(GetPos(), { (float)rot(random),0.0f,(float)rot(random) }, { 0.25f,0.25f,0.25f }, false);
	}
	for (int nNumCreate = 0; nNumCreate < NUM_PIECE; ++nNumCreate)
	{
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_int_distribution<int> rot(0, 3);
		CBlock_Piece::Create(GetPos(), { (float)rot(random),0.0f,(float)rot(random) }, { 0.3f,0.3f,0.3f }, true);
	}
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