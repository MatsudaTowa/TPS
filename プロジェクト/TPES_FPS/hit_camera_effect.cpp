//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g�uhit_camera_effect.cpp�v
// Author���c�i�v
//
//=============================================
#include "hit_camera_effect.h"
#include "manager.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CHitCameraEffect::m_pTextureTemp = nullptr;
const std::string CHitCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect002.png";

//=============================================
//�R���X�g���N�^
//=============================================
CHitCameraEffect::CHitCameraEffect(int nPriority): CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CHitCameraEffect::~CHitCameraEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CHitCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f);

	//�T�C�Y����
	SetSize(size);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CHitCameraEffect::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CHitCameraEffect::Update()
{
	//�e�N���X�̏I��
	CObject2D::Update();

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
}

//=============================================
//�`��
//=============================================
void CHitCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CHitCameraEffect* CHitCameraEffect::Create(D3DXVECTOR3 pos)
{
	CHitCameraEffect* pHitCameraEffect = new CHitCameraEffect;
	//CObject *pObject = Getobject();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	if (pHitCameraEffect != nullptr)
	{
		pHitCameraEffect->SetPos(pos); //pos�ݒ�

		pHitCameraEffect->m_alpha = 0.8f;

		pHitCameraEffect->SetType(OBJECT_TYPE_FADE); //�^�C�v�ݒ�

		pHitCameraEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pHitCameraEffect->Init();
	}
	return pHitCameraEffect;
}

//=============================================
//�A���t�@�l���Z
//=============================================
void CHitCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
