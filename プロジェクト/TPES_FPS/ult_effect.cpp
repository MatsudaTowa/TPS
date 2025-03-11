//=============================================
//
//�E���g�G�t�F�N�g�uult_effect.cpp�v
// Author���c�i�v
//
//=============================================
#include "ult_effect.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CUltEffect::TEXTURE_NAME = "data\\TEXTURE\\ult_effect.png";

//�F
const D3DXCOLOR CUltEffect::COLOR = { 1.0f,0.0f,0.0f, 0.75f };

//=============================================
//�R���X�g���N�^
//=============================================
CUltEffect::CUltEffect(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CUltEffect::~CUltEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CUltEffect::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	SetColor(COLOR);
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CUltEffect::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CUltEffect::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//�`��
//=============================================
void CUltEffect::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N���X�̕`��
	CObject3D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//����
//=============================================
CUltEffect* CUltEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CUltEffect* pUltEffect = new CUltEffect;

	// null�Ȃ�null��Ԃ�
	if (pUltEffect == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pUltEffect->SetPos(pos); //pos�ݒ�
	pUltEffect->SetSize(size); //�T�C�Y�ݒ�
	pUltEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�
	pUltEffect->SetType(OBJECT_TYPE_ULT_EFFECT); //�^�C�v�ݒ�
	pUltEffect->Init(); //����������

	return pUltEffect;
}
