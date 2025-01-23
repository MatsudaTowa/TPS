//=============================================
//
//�}�X�N����[mask.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "mask.h"
#include "manager.h"

//=============================================
// �R���X�g���N�^
//=============================================
CMask::CMask(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CMask::~CMask()
{
}

//=============================================
// ������
//=============================================
HRESULT CMask::Init()
{
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f });

	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.75f);

	//�J���[����
	SetColor(col);

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CMask::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CMask::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// �`��
//=============================================
void CMask::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// ��r�Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);
	// �X�e���V���}�X�N���w�肷��
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// �X�e���V����r�֐����w�肷�� TODO:�ȏ�ɂ���Ƃ��������Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// �X�e���V�����ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// Z�e�X�g�E�X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g�E�X�e���V���e�X�g���s
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g���s�E�X�e���V���e�X�g����

	CObject2D::Draw();

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================
// ����
//=============================================
CMask* CMask::Create()
{
	CMask* pMask = new CMask;

	if (pMask == nullptr) { return nullptr; }

	pMask->Init();

	return pMask;
}
