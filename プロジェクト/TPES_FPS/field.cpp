//=============================================
//
//3DTemplate[field.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "field.h"
#include "manager.h"

//tex�p�X
const std::string CField::TEXTURE_NAME = "data\\TEXTURE\\soil.jpg";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CField::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CField::CField(int nPriority) : CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CField::~CField()
{
}

//=============================================
//������
//=============================================
HRESULT CField::Init()
{
	// ���g�̃T�C�Y�擾
	D3DXVECTOR3 sizeThis = GetSize();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f,1.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CField::Update()
{

}

//=============================================
//�`��
//=============================================
void CField::Draw()
{
	// �e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//  ����
//=============================================
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CField* pField = new CField;

	// null�Ȃ�null��Ԃ�
	if (pField == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pField->SetPos(pos); //pos�ݒ�
	pField->SetSize(size); //�T�C�Y�ݒ�
	pField->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�
	pField->SetType(OBJECT_TYPE_FIELD); //�^�C�v�ݒ�
	pField->Init(); //���̏���������

	return pField;
}