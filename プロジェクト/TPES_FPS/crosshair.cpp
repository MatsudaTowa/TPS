//=============================================
//
//�N���X�w�A[crosshair.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "crosshair.h"
#include "manager.h"

const std::string CCrossHair::CROSSHAIR_TEXTURE_NAME = "data\\TEXTURE\\crosshair000.png";

//=============================================
//�R���X�g���N�^
//=============================================
CCrossHair::CCrossHair(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CCrossHair::~CCrossHair()
{
}

//=============================================
//������
//=============================================
HRESULT CCrossHair::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���ǂݍ���
	BindTexture(pTexture->GetAddress(pTexture->Regist(&CROSSHAIR_TEXTURE_NAME)));

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CCrossHair::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CCrossHair::Update()
{
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�`��
//=============================================
void CCrossHair::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�e�N���X�̕`��
	CBillboard::Draw();
	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//����
//=============================================
CCrossHair* CCrossHair::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CCrossHair* pCroshair = new CCrossHair;

	if (pCroshair == nullptr)
	{
		return nullptr;
	}

	pCroshair->SetPos(pos); //pos�ݒ�
	pCroshair->SetSize(size); //�T�C�Y�ݒ�
	pCroshair->SetRot(rot);
	pCroshair->SetColor(col);

	pCroshair->SetType(OBJECT_TYPE_RETICLE); //�^�C�v�ݒ�
	pCroshair->Init();

	return pCroshair;
}