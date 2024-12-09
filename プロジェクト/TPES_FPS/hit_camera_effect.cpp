//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g�uhit_camera_effect.cpp�v
// Author���c�i�v
//
//=============================================
#include "hit_camera_effect.h"
#include "hit_camera_effect_mild.h"
#include "hit_camera_effect_moderate.h"
#include "hit_camera_effect_severe.h"
#include "manager.h"

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
	SetVtx(1.0f, D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha));

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
	SetVtx(1.0f, D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha));
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
CHitCameraEffect* CHitCameraEffect::Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage)
{
	CHitCameraEffect* pHitCameraEffect = nullptr;
	//CObject *pObject = Getobject();

	switch (stage)
	{
	case CHitCameraEffect::MILD:
		pHitCameraEffect = new CHitCameraEffectMild;
		break;
	case CHitCameraEffect::MODERATE:
		pHitCameraEffect = new CHitCameraEffectModerate;
		break;
	case CHitCameraEffect::SEVERE:
		pHitCameraEffect = new CHitCameraEffectSevere;
		break;
	default:
		assert(false);
		break;
	}

	if (pHitCameraEffect == nullptr) {return nullptr;}

	pHitCameraEffect->SetPos(pos); //pos�ݒ�

	pHitCameraEffect->m_alpha = 0.8f;

	pHitCameraEffect->SetType(OBJECT_TYPE_HIT_CAMERA_EFFECT); //�^�C�v�ݒ�

	pHitCameraEffect->Init();

	return pHitCameraEffect;
}

//=============================================
//�A���t�@�l���Z
//=============================================
void CHitCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
