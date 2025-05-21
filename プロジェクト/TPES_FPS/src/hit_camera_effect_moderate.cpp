//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(������)�uhit_camera_effect_mild.cpp�v
// Author���c�i�v
//
//=============================================
#include "hit_camera_effect_moderate.h"
#include "manager.h"

const std::string CHitCameraEffectModerate::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect001.png";

//=============================================
//�R���X�g���N�^
//=============================================
CHitCameraEffectModerate::CHitCameraEffectModerate(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CHitCameraEffectModerate::~CHitCameraEffectModerate()
{
}

//=============================================
//������
//=============================================
HRESULT CHitCameraEffectModerate::Init()
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
void CHitCameraEffectModerate::Uninit()
{
	//�e�N���X�̏I��
	CHitCameraEffect::Uninit();
}

//=============================================
//�X�V
//=============================================
void CHitCameraEffectModerate::Update()
{
	//�e�N���X�̍X�V
	CHitCameraEffect::Update();
}

//=============================================
//�`��
//=============================================
void CHitCameraEffectModerate::Draw()
{
	//�e�N���X�̕`��
	CHitCameraEffect::Draw();
}
