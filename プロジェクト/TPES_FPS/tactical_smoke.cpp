//=============================================
//
//�X���[�N����[tactical_somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tactical_smoke.h"
#include "manager.h"

//�J���[
const D3DXCOLOR CTacticalSmoke::COLOR = { 1.0f,1.0f,1.0f,1.0f };

//�X���[�N�̃T�C�Y
const D3DXVECTOR3 CTacticalSmoke::SIZE = { 60.0f,60.0f,0.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CTacticalSmoke::CTacticalSmoke(int nPriority):CSmoke(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTacticalSmoke::~CTacticalSmoke()
{
}

//=============================================
//������
//=============================================
HRESULT CTacticalSmoke::Init()
{
	//�e�N���X�̏�����
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
	move = { number_x(random) ,number_y(random) ,number_z(random) };

	//�ړ��ʐݒ�
	SetMove(move);

	//�F�ݒ�
	SetColor(COLOR);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTacticalSmoke::Uninit()
{
	//�e�N���X�̏I��
	CSmoke::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTacticalSmoke::Update()
{
	//�e�N���X�̍X�V
	CSmoke::Update();

	D3DXVECTOR3 move = GetMove();
	//�ړ��ʑ��
	if (move.x > FLOAT_ZERO)
	{
		move.x -= X_DECREASE;
	}
	if (move.x < FLOAT_ZERO)
	{
		move.x += X_DECREASE;
	}


	//�ړ��ʐݒ�
	SetMove(move);
}

//=============================================
//�`��
//=============================================
void CTacticalSmoke::Draw()
{
	//�e�N���X�̕`��
	CSmoke::Draw();
}
