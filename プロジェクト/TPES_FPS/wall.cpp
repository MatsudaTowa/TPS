//=============================================
//
//�ǂ̏���[wall.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wall.h"
#include "manager.h"

//tex�p�X
const std::string CWall::TEXTURE_NAME = "data\\TEXTURE\\effect000.jpg";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CWall::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CWall::CWall(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWall::~CWall()
{
}

//=============================================
//������
//=============================================
HRESULT CWall::Init()
{
	// ���g�̃T�C�Y�擾
	D3DXVECTOR3 sizeThis = GetSize();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CObject3D::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWall::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWall::Update()
{
	CObject3D::Update();
}

//=============================================
//�`��
//=============================================
void CWall::Draw()
{
	CObject3D::Draw();
}

//=============================================
//����
//=============================================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CWall* pWall = new CWall;

	// null�Ȃ�null��Ԃ�
	if (pWall == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pWall->SetPos(pos); //pos�ݒ�
	pWall->SetRot(rot); //rot�ݒ�
	pWall->SetSize(size); //�T�C�Y�ݒ�
	pWall->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�
	pWall->SetType(OBJECT_TYPE_WALL); //�^�C�v�ݒ�
	pWall->Init(); //���̏���������

	return pWall;
}
