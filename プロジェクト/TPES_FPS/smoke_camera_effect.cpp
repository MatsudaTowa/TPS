//=============================================
//
//�X���[�N�̃J�����G�t�F�N�g�uhit_camera_effect.cpp�v
// Author���c�i�v
//
//=============================================
#include "smoke_camera_effect.h"
#include "manager.h"

//�J�����̃G�t�F�N�g�e�N�X�`��
const std::string CSmokeCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\smoke_camera_effect.png";

//=============================================
//�R���X�g���N�^
//=============================================
CSmokeCameraEffect::CSmokeCameraEffect(int nPriority):CObject2D(nPriority),
m_alpha(FLOAT_ONE)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmokeCameraEffect::~CSmokeCameraEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CSmokeCameraEffect::Init()
{
	CObject2D::Init();

	//�ʒu�ݒ�
	SetPos({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f });

	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * HALF, SCREEN_HEIGHT * HALF);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(FLOAT_ONE, FLOAT_ONE, FLOAT_ONE, m_alpha);

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(FLOAT_ONE);

	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmokeCameraEffect::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmokeCameraEffect::Update()
{
	//�e�N���X�̏I��
	CObject2D::Update();

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(FLOAT_ONE, FLOAT_ONE, FLOAT_ONE, m_alpha);

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(FLOAT_ONE);
}

//=============================================
//�`��
//=============================================
void CSmokeCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CSmokeCameraEffect* CSmokeCameraEffect::Create()
{
	CSmokeCameraEffect* pSmokeCameraEffect = new CSmokeCameraEffect;

	if (pSmokeCameraEffect == nullptr) { return nullptr; }

	pSmokeCameraEffect->SetType(OBJECT_TYPE_SMOKE_CAMERA_EFFECT); //�^�C�v�ݒ�

	pSmokeCameraEffect->Init();

	return pSmokeCameraEffect;
}

//=============================================
//�A���t�@�l���Z
//=============================================
void CSmokeCameraEffect::SubAlpha()
{
	m_alpha -= FADE_VALUE;
}
