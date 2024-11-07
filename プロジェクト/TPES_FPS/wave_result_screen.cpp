//=============================================
//
//�E�F�[�u���U���g���[wave_result_screen.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_result_screen.h"

//=============================================
//�R���X�g���N�^
//=============================================
CWave_Result_Screen::CWave_Result_Screen(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWave_Result_Screen::~CWave_Result_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CWave_Result_Screen::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�������g�̃T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//�T�C�Y����
	SetSize(size);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.85f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWave_Result_Screen::Uninit()
{
	//�e�N���X�̏I�����Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWave_Result_Screen::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CWave_Result_Screen::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CWave_Result_Screen* CWave_Result_Screen::Create(D3DXVECTOR3 pos)
{
	//CTexture* pTexture = CManager::GetTexture();
	CWave_Result_Screen* pWave_Result_Screen = new CWave_Result_Screen;

	//null�Ȃ�null��Ԃ�
	if (pWave_Result_Screen == nullptr) { return nullptr; }

	pWave_Result_Screen->SetPos(pos); //pos�ݒ�

	pWave_Result_Screen->SetType(OBJECT_TYPE_RESULT); //�^�C�v�ݒ�

	//pResult_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pWave_Result_Screen->Init();

	return pWave_Result_Screen;
}
