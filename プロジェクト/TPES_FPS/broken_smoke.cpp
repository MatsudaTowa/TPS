//=============================================
//
//�X���[�N����[broken_somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "broken_smoke.h"

const D3DXCOLOR CBrokenSmoke::COLOR = { 0.1f,0.1f,0.1f,1.0f };

//�X���[�N�̃T�C�Y
const D3DXVECTOR3 CBrokenSmoke::SIZE = { 30.0f,30.0f,0.0f };
//=============================================
//�R���X�g���N�^
//=============================================
CBrokenSmoke::CBrokenSmoke(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBrokenSmoke::~CBrokenSmoke()
{
}

//=============================================
//������
//=============================================
HRESULT CBrokenSmoke::Init()
{
	CSmoke::Init();

	//�T�C�Y���
	SetSize(SIZE);

	std::random_device seed;
	std::mt19937 random(seed());

	//���ꂼ��̕����ւ̈ړ��ʃ����_���Őݒ�
	std::uniform_real_distribution<float> number_x(MOVE_X_MIN, MOVE_X_MAX);
	std::uniform_real_distribution<float> number_y(MOVE_Y_MIN, MOVE_Y_MAX);
	std::uniform_real_distribution<float> number_z(MOVE_Z_MIN, MOVE_Z_MAX);

	D3DXVECTOR3 move = GetMove();
	//�ړ��ʑ��
	move = { number_x(random),number_y(random),number_z(random)};

	SetMove(move);

	SetColor(COLOR);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBrokenSmoke::Uninit()
{
	CSmoke::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBrokenSmoke::Update()
{
	CSmoke::Update();
}

//=============================================
//�`��
//=============================================
void CBrokenSmoke::Draw()
{
	CSmoke::Draw();
}
