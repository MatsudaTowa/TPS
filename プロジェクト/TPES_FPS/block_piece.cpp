//=============================================
//
//�u���b�N�̔j��[block_piece.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "block_piece.h"

//x�t�@�C���p�X
const char* CBlock_Piece::MODEL_NAME[CBlock_Piece::PIECE_SHAPE_MAX]
{
	"data\\MODEL\\piece_000.x",
	"data\\MODEL\\piece_001.x",
	"data\\MODEL\\piece_002.x",
};

//=============================================
// �R���X�g���N�^
//=============================================
CBlock_Piece::CBlock_Piece(int nPriority):CObjectX(nPriority),
m_shape()		//�s�[�X�̌`
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

	//�������̂Ɠ����Ȃ����̂Ŋm�ۂ���N���X��ύX
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

	int nShape = 0;
	//pPiece->m_type = type;
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, CBlock_Piece::PIECE_SHAPE_MAX - 1);
	//�����_���Ń^�C�v�w��
	nShape = number(random);

	//���̈ʒu���炩��ǂꂾ����������
	std::uniform_real_distribution<float> pos_shift_x(SHIFT_X_MIN, SHIFT_X_MAX);
	std::uniform_real_distribution<float> pos_shift_z(SHIFT_Z_MIN, SHIFT_Z_MIN);

	pPiece->m_shape = (CBlock_Piece::PIECE_SHAPE)nShape;
	pPiece->SetPos({ pos .x + pos_shift_x(random),0.2f,pos.z + pos_shift_z(random)}); //pos�ݒ�
	pPiece->SetRot(rot); //rot�ݒ�
	pPiece->SetScale(scale); //�X�P�[���ݒ�
	//pPiece->BindTexture(m_pTextureTemp);

	//X�t�@�C���ǂݍ���
	pPiece->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).pMesh);

	pPiece->SetType(OBJECT_TYPE_BLOCK_PIECE); //�^�C�v�ݒ�
	pPiece->Init();

	return pPiece;
}

//=============================================
// �R���X�g���N�^
//=============================================
CMove_Piece::CMove_Piece(int nPriority):CBlock_Piece(nPriority),
m_nLife(INT_ZERO),					//����
m_move(VEC3_RESET_ZERO)				//�ړ���
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
	// �e�N���X�̏�����
	CBlock_Piece::Init();

	//��΂�����
	float fVertex;
	//�ړ���
	float fMove;

	//���ˏ�Ƀ����_��
	fVertex = CICRLE_RAND;

	//�ړ������_��(�Œ�ł�MIN_MOVE�͑�������悤�ɐ݌v)
	fMove = (float)(rand() % RAND_RANGE) / MOVE_RANGE + MIN_MOVE;

	//�������
	m_nLife = LIFE;

	//�ړ��ʑ��
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
	// �e�N���X�̏I��
	CBlock_Piece::Uninit();
}

//=============================================
// �X�V
//=============================================
void CMove_Piece::Update()
{
	// �e�N���X�̍X�V
	CBlock_Piece::Update();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ�����
	pos += m_move;
	//�ʒu���
	SetPos(pos);

	//���������炷
	--m_nLife;
	if (m_nLife <= INT_ZERO)
	{//���C�t�؂ꂽ��
		m_nLife = INT_ZERO;
		//�j��
		Uninit();
	}
}

//=============================================
// �`��
//=============================================
void CMove_Piece::Draw()
{
	// �e�N���X�̕`��
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
	// �e�N���X�̏�����
	CBlock_Piece::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CStack_Piece::Uninit()
{
	// �e�N���X�̏I��
	CBlock_Piece::Uninit();
}

//=============================================
// �X�V
//=============================================
void CStack_Piece::Update()
{
	// �e�N���X�̍X�V
	CBlock_Piece::Update();
}

//=============================================
// �`��
//=============================================
void CStack_Piece::Draw()
{
	// �e�N���X�̕`��
	CBlock_Piece::Draw();
}
