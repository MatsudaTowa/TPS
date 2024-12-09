//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(�y����)�uhit_camera_effect_mild.cpp�v
// Author���c�i�v
//
//=============================================
#include "hit_camera_effect_mild.h"
#include "manager.h"

const std::string CHitCameraEffectMild::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect000.png";

//=============================================
//�R���X�g���N�^
//=============================================
CHitCameraEffectMild::CHitCameraEffectMild(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CHitCameraEffectMild::~CHitCameraEffectMild()
{
}

//=============================================
//������
//=============================================
HRESULT CHitCameraEffectMild::Init()
{
	//�e�N���X�̏�����
	CHitCameraEffect::Init();

	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CHitCameraEffectMild::Uninit()
{
	//�e�N���X�̏I��
	CHitCameraEffect::Uninit();
}

//=============================================
//�X�V
//=============================================
void CHitCameraEffectMild::Update()
{
	//�e�N���X�̍X�V
	CHitCameraEffect::Update();
}

//=============================================
//�`��
//=============================================
void CHitCameraEffectMild::Draw()
{
	//�e�N���X�̕`��
	CHitCameraEffect::Draw();
}
