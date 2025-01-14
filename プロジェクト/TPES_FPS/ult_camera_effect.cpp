//=============================================
//
//�E���g���̃J�����G�t�F�N�g�uult_camera_effect.cpp�v
// Author���c�i�v
//
//=============================================
#include "ult_camera_effect.h"
#include "manager.h"

const std::string CUltCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\syutyu90.png";

//=============================================
//�R���X�g���N�^
//=============================================
CUltCameraEffect::CUltCameraEffect(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CUltCameraEffect::~CUltCameraEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CUltCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha);

	//�J���[����
	SetColor(col);

	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//���_�ݒ�
	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CUltCameraEffect::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CUltCameraEffect::Update()
{
	//�e�N���X�̏I��
	CObject2D::Update();

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha);

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CUltCameraEffect::Draw()
{
	CObject2D::Draw();

}

//=============================================
//����
//=============================================
CUltCameraEffect* CUltCameraEffect::Create(D3DXVECTOR3 pos)
{
	CUltCameraEffect* pUltCameraEffect = new CUltCameraEffect;
	//CObject *pObject = Getobject();

	if (pUltCameraEffect == nullptr) { return nullptr; }

	pUltCameraEffect->SetPos(pos); //pos�ݒ�

	pUltCameraEffect->m_alpha = 0.8f;

	pUltCameraEffect->SetType(OBJECT_TYPE_ULT_CAMERA_EFFECT); //�^�C�v�ݒ�

	pUltCameraEffect->Init();

	return pUltCameraEffect;
}

//=============================================
//�A���t�@�l����
//=============================================
void CUltCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
