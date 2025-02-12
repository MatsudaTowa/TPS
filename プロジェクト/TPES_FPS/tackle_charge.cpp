//=============================================
//
//�^�b�N���`���[�W���̃G�t�F�N�g[tackle_charge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tackle_charge.h"
#include "manager.h"

//�ǂݍ��ރu���b�N���̃t�@�C��
const std::string CTackleCharge::TEXTURE_NAME = "data\\TEXTURE\\ult_effect.png";
const D3DXVECTOR3 CTackleCharge::SIZE = {180.0f,180.0f,0.0f};

//=============================================
//�R���X�g���N�^
//=============================================
CTackleCharge::CTackleCharge(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTackleCharge::~CTackleCharge()
{
}

//=============================================
//������
//=============================================
HRESULT CTackleCharge::Init()
{
	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//�e�N�X�`���ݒ�
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); 

	//�e�N���X�̏�����
	CBillboard::Init();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTackleCharge::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTackleCharge::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�`��
//=============================================
void CTackleCharge::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N���X�̕`��
	CBillboard::Draw();

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//����
//=============================================
CTackleCharge* CTackleCharge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CTackleCharge* pTackleCharge = new CTackleCharge;

	if (pTackleCharge == nullptr) { return nullptr; }

	pTackleCharge->SetPos(pos);
	pTackleCharge->SetSize(size);
	pTackleCharge->SetColor(col);
	pTackleCharge->SetType(OBJECT_TYPE_EFFECT);

	pTackleCharge->Init();

	return pTackleCharge;
}
