//=============================================
//
//�X���[�N����[tactical_somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tactical_smoke.h"
#include "manager.h"

//�J���[�ʐ�
const D3DXCOLOR CTacticalSmoke::COLOR = { 1.0f,1.0f,1.0f,1.0f };

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
}

//=============================================
//�`��
//=============================================
void CTacticalSmoke::Draw()
{
	//�e�N���X�̕`��
	CSmoke::Draw();
}
