//=============================================
// 
//�}�Y���t���b�V��[muzzle_flash.h]
//Auther Matsuda Towa
//
//=============================================
#include "muzzle_flash.h"
#include "manager.h"

const std::string CMuzzleFlash::TEXTURE_NAME = "data\\TEXTURE\\flash.png";
const D3DXVECTOR3 CMuzzleFlash::SIZE = { 10.0f,10.0f,0.0f };
//=============================================
//�R���X�g���N�^
//=============================================
CMuzzleFlash::CMuzzleFlash(int nPriority):CBillboard(nPriority),
m_nLife(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMuzzleFlash::~CMuzzleFlash()
{
}

//=============================================
//������
//=============================================
HRESULT CMuzzleFlash::Init()
{
	//�e�̏�����
	CBillboard::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���ǂݍ���
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMuzzleFlash::Uninit()
{
	//�e�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMuzzleFlash::Update()
{

	--m_nLife; //�̗͌���
	if (m_nLife > 0)
	{
		//�e�̍X�V
		CBillboard::Update();

		//���_���W
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	}
	else if(m_nLife <= 0)
	{
		m_nLife = 0;
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CMuzzleFlash::Draw()
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
CMuzzleFlash* CMuzzleFlash::Create(D3DXVECTOR3 pos)
{
	CMuzzleFlash* pMuzzleFlash = new CMuzzleFlash;
	if (pMuzzleFlash == nullptr) { return nullptr; }

	//�ʒu���
	pMuzzleFlash->SetPos(pos);

	//�T�C�Y���
	pMuzzleFlash->SetSize(SIZE);

	//�̗͐ݒ�
	pMuzzleFlash->m_nLife = LIFE;

	pMuzzleFlash->Init();

	pMuzzleFlash->SetType(OBJECT_TYPE_MUZZLE_FLUSH);

	return pMuzzleFlash;
}
