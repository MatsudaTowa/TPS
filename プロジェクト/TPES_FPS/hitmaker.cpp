//=============================================
//
//�q�b�g�}�[�J�[[hitmaker.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "hitmaker.h"
#include "manager.h"

const std::string CHitMaker::HITMARKER_DOT_TEXTURE_NAME = "data\\TEXTURE\\hitmarker.png";


//=============================================
//�R���X�g���N�^
//=============================================
CHitMaker::CHitMaker(int nPriority):CBillboard(nPriority),
m_nLife(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CHitMaker::~CHitMaker()
{
}

//=============================================
//������
//=============================================
HRESULT CHitMaker::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���ǂݍ���
	BindTexture(pTexture->GetAddress(pTexture->Regist(&HITMARKER_DOT_TEXTURE_NAME)));

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CHitMaker::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CHitMaker::Update()
{
	CBillboard::Update();

	D3DXCOLOR col = GetColor();
	col.a -= 0.05f;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	SetColor(col);

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�`��
//=============================================
void CHitMaker::Draw()
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
//�e������������F�ύX
//=============================================
void CHitMaker::HitColor(D3DXCOLOR col)
{
	SetColor(col);
}

//=============================================
//����
//=============================================
CHitMaker* CHitMaker::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CHitMaker* pHitMaker = new CHitMaker;

	if (pHitMaker == nullptr)
	{
		return nullptr;
	}

	pHitMaker->SetPos(pos); //pos�ݒ�
	pHitMaker->SetSize(size); //�T�C�Y�ݒ�
	pHitMaker->SetRot(rot);
	pHitMaker->SetColor(col);

	pHitMaker->SetType(OBJECT_TYPE_RETICLE); //�^�C�v�ݒ�
	pHitMaker->Init();

	return pHitMaker;
}
