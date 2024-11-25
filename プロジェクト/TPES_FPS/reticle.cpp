//=============================================
//
//���e�B�N��[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CReticle::m_pTextureTemp = nullptr;
const std::string CReticle::RETICLE_TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//=============================================
//�R���X�g���N�^
//=============================================
CReticle::CReticle(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CReticle::~CReticle()
{
}

//=============================================
//������
//=============================================
HRESULT CReticle::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CReticle::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CReticle::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================
//�`��
//=============================================
void CReticle::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CReticle* CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CReticle* pRaticle = new CReticle;

	if (pRaticle == nullptr) 
	{
		return nullptr; 
	}

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pRaticle->SetPos(pos); //pos�ݒ�
	pRaticle->SetSize(size); //�T�C�Y�ݒ�
	pRaticle->SetRot(rot);
	pRaticle->BindTexture(pTexture->GetAddress(pTexture->Regist(&RETICLE_TEXTURE_NAME)));

	pRaticle->SetType(OBJECT_TYPE_RETICLE); //�^�C�v�ݒ�
	pRaticle->Init();

	return pRaticle;
}

//=============================================
//�ړ�����
//=============================================
void CReticle::Move()
{

}
