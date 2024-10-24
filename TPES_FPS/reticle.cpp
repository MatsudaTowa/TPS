//=============================================
//
//���e�B�N��[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CReticle::CReticle(int nPriority)
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
	CReticle* pRaticle = nullptr;

	if (pRaticle == nullptr) 
	{
		return nullptr; 
	}

	CTexture* pTexture = CManager::GetTexture();

	pRaticle->SetPos(pos); //pos�ݒ�
	pRaticle->SetSize(size); //�T�C�Y�ݒ�
	pRaticle->SetRot(rot);

	pRaticle->SetType(OBJECT_TYPE_RETICLE); //�^�C�v�ݒ�
	pRaticle->Init();

	return pRaticle;
}

//=============================================
//�ړ�����
//=============================================
void CReticle::Move()
{
	//�}�E�X�̏��擾
	CInputMouse* pMouse = CManager::GetMouse();
}
