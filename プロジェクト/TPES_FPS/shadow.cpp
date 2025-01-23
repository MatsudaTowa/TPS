//=============================================
//
//�e�ushadow.h�v
// Author���c�i�v
//
//=============================================
#include "shadow.h"
#include "manager.h"

const std::string CShadow::TEXTURE_NAME = "data\\TEXTURE\\effect000.jpg";

//=============================================
//�R���X�g���N�^
//=============================================
CShadow::CShadow(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CShadow::~CShadow()
{
}

//=============================================
//������
//=============================================
HRESULT CShadow::Init()
{
	CObject3D::Init();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CShadow::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CShadow::Update()
{
	CObject3D::Update();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//�`��
//=============================================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//���Z��������
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//����
//=============================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CShadow* pShadow = new CShadow;

	// null�Ȃ�null��Ԃ�
	if (pShadow == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pShadow->SetPos(pos); //pos�ݒ�
	pShadow->SetSize(size); //�T�C�Y�ݒ�
	pShadow->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�
	pShadow->SetType(OBJECT_TYPE_SHADOW); //�^�C�v�ݒ�
	pShadow->Init(); //�e�̏���������

	return pShadow;
}
