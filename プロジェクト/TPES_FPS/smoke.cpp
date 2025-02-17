//=============================================
//
//�X���[�N����[somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke.h"
#include "smoke_range.h"
#include "manager.h"
#include "tactical_smoke.h"
#include "broken_smoke.h"

//�e�N�X�`���p�X
const std::string CSmoke::SMOKE_TEXTURE_NAME = "data\\TEXTURE\\effect002.tga";

//=============================================
//�R���X�g���N�^
//=============================================
CSmoke::CSmoke(int nPriority) : CBillboard(nPriority),m_nLife(INT_ZERO),m_move(VEC3_RESET_ZERO)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmoke::~CSmoke()
{
}

//=============================================
//������
//=============================================
HRESULT CSmoke::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();

	//���C�t�ݒ�
	m_nLife = SMOKE_LIFE; 

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmoke::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmoke::Update()
{
	//�e�N���X�̃A�b�v�f�[�g
	CObject3D::Update();

	//�ړ�����
	Move();

	if (m_nLife > INT_ZERO)
	{//���C�t���c���Ă����
		//���C�t��1���炷
		--m_nLife;
	}
	else
	{//���C�t���Ȃ����
		//�t�F�[�h�A�E�g
		FadeOut();
	}
}

//=============================================
//�ړ�����
//=============================================
void CSmoke::Move()
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʑ��
	pos += m_move;

	//�ʒu�ݒ�
	SetPos(pos);

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�t�F�[�h�A�E�g
//=============================================
void CSmoke::FadeOut()
{
	//�F�擾
	D3DXCOLOR color = GetColor();

	if (color.a > FLOAT_ZERO)
	{//�����x��0��荂��������
		//���Z
		color.a -= FADE_VALUE;
		//�F���
		SetColor(color);
	}
	else
	{//�����Ȃ��Ȃ�����
		//SE���~�߂�
		CManager::GetInstance()->GetSound()->StopSound(CSound::SOUND_LABEL_SE_SMOKE);
		//�I��
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CSmoke::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�r���{�[�h�̕`�揈��
	CBillboard::Draw();

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
	CBillboard::Draw();

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//����
//=============================================
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, SMOKE_TYPE type)
{
	CSmoke* pSmoke = nullptr;

	switch (type)
	{
	case CSmoke::SMOKE_TYPE_TACTICAL:
		pSmoke = new CTacticalSmoke;
		break;
	case CSmoke::SMOKE_TYPE_BROKEN:
		pSmoke = new CBrokenSmoke;
		break;
	default:
		assert(false);
		break;
	}

	if(pSmoke == nullptr) {return nullptr;}

	pSmoke->SetPos(pos);
	pSmoke->Init();
	pSmoke->SetType(OBJECT_TYPE_SMOKE);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pSmoke->BindTexture(pTexture->GetAddress(pTexture->Regist(&SMOKE_TEXTURE_NAME)));

	return pSmoke;
}
