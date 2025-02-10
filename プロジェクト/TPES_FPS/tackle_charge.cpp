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
}

//=============================================
//�`��
//=============================================
void CTackleCharge::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
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

	pTackleCharge->Init();

	return pTackleCharge;
}
