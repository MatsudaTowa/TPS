//=============================================
//
//�u���b�N�̔j��[block_piece.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "block_piece.h"

const char* CBlock_Piece::MODEL_NAME[CBlock_Piece::PIECE_TYPE_MAX]
{
	"data\\MODEL\\piece_000.x",
	"data\\MODEL\\piece_001.x",
	"data\\MODEL\\piece_002.x",
};
//=============================================
// �R���X�g���N�^
//=============================================
CBlock_Piece::CBlock_Piece(int nPriority):CObjectX(nPriority),
m_type()
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CBlock_Piece::~CBlock_Piece()
{
}

//=============================================
// ������
//=============================================
HRESULT CBlock_Piece::Init()
{
	//�e�N���X�̏���������
	CObjectX::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CBlock_Piece::Uninit()
{
	//�e�N���X�̏I������
	CObjectX::Uninit();
}

//=============================================
// �X�V
//=============================================
void CBlock_Piece::Update()
{
	//�e�N���X�̍X�V����
	CObjectX::Update();
}

//=============================================
// �`��
//=============================================
void CBlock_Piece::Draw()
{
	//�e�N���X�̕`�揈��
	CObjectX::Draw();
}

//=============================================
// ����
//=============================================
CBlock_Piece* CBlock_Piece::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, bool isMove)
{
	CBlock_Piece* pPiece = nullptr;

	if (isMove)
	{
		pPiece = new CMove_Piece;
	}
	else if (!isMove)
	{
		pPiece = new CStack_Piece;
	}

	//null�Ȃ�null��Ԃ�
	if (pPiece == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();
	CTexture* pTex = CManager::GetInstance()->GetTexture();

	int nType = 0;
	//pPiece->m_type = type;
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, CBlock_Piece::PIECE_TYPE_MAX - 1);
	//�����_���Ń^�C�v�w��
	nType = number(random);

	//���̈ʒu���炩��ǂꂾ����������
	std::uniform_int_distribution<int> pos_shift_x(-50, 50);
	std::uniform_int_distribution<int> pos_shift_z(-50, 50);

	pPiece->m_type = (CBlock_Piece::PIECE_TYPE)nType;
	pPiece->SetPos({ pos .x + pos_shift_x(random),0.2f,pos.z + pos_shift_z(random)}); //pos�ݒ�
	pPiece->SetRot(rot); //rot�ݒ�
	pPiece->SetScale(scale); //�X�P�[���ݒ�
	//pPiece->BindTexture(m_pTextureTemp);

	//X�t�@�C���ǂݍ���
	pPiece->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).pMesh);

	pPiece->SetType(OBJECT_TYPE_BLOCK_PIECE); //�^�C�v�ݒ�
	pPiece->Init();

	return pPiece;
}

//=============================================
// �R���X�g���N�^
//=============================================
CMove_Piece::CMove_Piece(int nPriority):CBlock_Piece(nPriority),
m_nLife(0),
m_move({0.0f,0.0f,0.0f})
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CMove_Piece::~CMove_Piece()
{
}

//=============================================
// ������
//=============================================
HRESULT CMove_Piece::Init()
{
	CBlock_Piece::Init();

	float fVertex;
	float fMove;

	//���ˏ�Ƀ����_��
	fVertex = (float)(rand() % 629 - 314) / 100.0f;

	//�ړ���1�ȏ�2.0�ȉ���
	fMove = (float)(rand() % 101) / 10.0f + 5.0f;

	m_nLife = LIFE;

	m_move.x = sinf(fVertex) * fMove;
	m_move.y = fMove;
	m_move.z = cosf(fVertex) * fMove;
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CMove_Piece::Uninit()
{
	CBlock_Piece::Uninit();
}

//=============================================
// �X�V
//=============================================
void CMove_Piece::Update()
{
	CBlock_Piece::Update();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ�����
	pos += m_move;
	//�ʒu���
	SetPos(pos);

	--m_nLife;
	if (m_nLife <= 0)
	{//���C�t�؂ꂽ��
		m_nLife = 0;
		//�j��
		Uninit();
	}
}

//=============================================
// �`��
//=============================================
void CMove_Piece::Draw()
{
	CBlock_Piece::Draw();
}

//=============================================
// �R���X�g���N�^
//=============================================
CStack_Piece::CStack_Piece(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CStack_Piece::~CStack_Piece()
{
}

//=============================================
// ������
//=============================================
HRESULT CStack_Piece::Init()
{
	CBlock_Piece::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CStack_Piece::Uninit()
{
	CBlock_Piece::Uninit();
}

//=============================================
// �X�V
//=============================================
void CStack_Piece::Update()
{
	CBlock_Piece::Update();
}

//=============================================
// �`��
//=============================================
void CStack_Piece::Draw()
{
	CBlock_Piece::Draw();
}
