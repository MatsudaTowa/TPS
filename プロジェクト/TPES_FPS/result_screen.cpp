//=============================================
//
//3DTemplate[result_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "result_screen.h"
#include "manager.h"

//tex�p�X
const std::string CResult_Screen::TEXTURE_NAME = "data\\TEXTURE\\result.png";

//=============================================
//�R���X�g���N�^
//=============================================
CResult_Screen::CResult_Screen(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CResult_Screen::~CResult_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CResult_Screen::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�������g�̃T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * HALF, SCREEN_HEIGHT * HALF);

	//�e�N�X�`�����W�ݒ�
	SetTexPos(VEC2_RESET_ONE);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = COLOR_WHITE;

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(FLOAT_ONE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CResult_Screen::Uninit()
{
	//�e�N���X�̏I�����Ă�
	CObject2D::Uninit();

}

//=============================================
//�X�V
//=============================================
void CResult_Screen::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CResult_Screen::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CResult_Screen* CResult_Screen::Create(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CResult_Screen* pResult_Screen = new CResult_Screen;

	//null�Ȃ�null��Ԃ�
	if (pResult_Screen == nullptr) {return nullptr;}

	pResult_Screen->SetPos(pos); //pos�ݒ�

	pResult_Screen->SetType(OBJECT_TYPE_RESULT); //�^�C�v�ݒ�

	pResult_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pResult_Screen->Init();

	return pResult_Screen;
}
