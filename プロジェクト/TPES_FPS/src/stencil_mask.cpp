//=============================================
//
//�X�e���V���}�X�N����[stencil_mask.cpp]
//Author Matsuda Towa
//
//=============================================
#include "stencil_mask.h"
#include "manager.h"

//�F
const D3DXCOLOR CStencilMask::COLOR = { 1.0f, 0.0f, 0.0f, 0.75f };

//=============================================
// �R���X�g���N�^
//=============================================
CStencilMask::CStencilMask(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CStencilMask::~CStencilMask()
{
}

//=============================================
// ������
//=============================================
HRESULT CStencilMask::Init()
{
	CMask::Init();
	//�F�ݒ�
	SetColor(COLOR);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CStencilMask::Uninit()
{
	CMask::Uninit();
}

//=============================================
// �X�V
//=============================================
void CStencilMask::Update()
{
	CMask::Update();
}

//=============================================
// �`��
//=============================================
void CStencilMask::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// ��r�Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, REFARENCE_VALUE);
	// �X�e���V���}�X�N���w�肷��
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// �X�e���V����r�֐����w�肷��
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
	// �X�e���V�����ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// Z�e�X�g�E�X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g�E�X�e���V���e�X�g���s
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g���s�E�X�e���V���e�X�g����

	CMask::Draw();

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
