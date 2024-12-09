//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(�d����)�uhit_camera_effect_severe.h�v
// Author���c�i�v
//
//=============================================
#include "hit_camera_effect_severe.h"
#include "manager.h"

const std::string CHitCameraEffectSevere::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect002.png";

//=============================================
//�R���X�g���N�^
//=============================================
CHitCameraEffectSevere::CHitCameraEffectSevere(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CHitCameraEffectSevere::~CHitCameraEffectSevere()
{
}

//=============================================
//������
//=============================================
HRESULT CHitCameraEffectSevere::Init()
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
void CHitCameraEffectSevere::Uninit()
{
	//�e�N���X�̏I��
	CHitCameraEffect::Uninit();
}

//=============================================
//�X�V
//=============================================
void CHitCameraEffectSevere::Update()
{
	//�e�N���X�̍X�V
	CHitCameraEffect::Update();
}

//=============================================
//�`��
//=============================================
void CHitCameraEffectSevere::Draw()
{
	//�e�N���X�̕`��
	CHitCameraEffect::Draw();
}
