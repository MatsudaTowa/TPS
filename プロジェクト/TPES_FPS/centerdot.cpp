//=============================================
//
//�Z���^�[�h�b�g[centerdot.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "centerdot.h"
#include "manager.h"

const std::string CCenterDot::CENTERDOT_TEXTURE_NAME = "data\\TEXTURE\\crosshair001.png";

//=============================================
//�R���X�g���N�^
//=============================================
CCenterDot::CCenterDot(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CCenterDot::~CCenterDot()
{
}

//=============================================
//������
//=============================================
HRESULT CCenterDot::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���ǂݍ���
	BindTexture(pTexture->GetAddress(pTexture->Regist(&CENTERDOT_TEXTURE_NAME)));

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CCenterDot::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CCenterDot::Update()
{
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�`��
//=============================================
void CCenterDot::Draw()
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
CCenterDot* CCenterDot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CCenterDot* pCenterDot = new CCenterDot;

	if (pCenterDot == nullptr)
	{
		return nullptr;
	}

	pCenterDot->SetPos(pos); //pos�ݒ�
	pCenterDot->SetSize(size); //�T�C�Y�ݒ�
	pCenterDot->SetRot(rot);
	pCenterDot->SetColor(col);

	pCenterDot->SetType(OBJECT_TYPE_RETICLE); //�^�C�v�ݒ�
	pCenterDot->Init();

	return pCenterDot;
}
