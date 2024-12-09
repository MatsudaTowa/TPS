//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(�d����)�uhit_camera_effect_severe.h�v
// Author���c�i�v
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_SEVERE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _HIT_CAMERA_EFFECT_SEVERE_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//�q�b�g���̃J�����G�t�F�N�g�N���X
//=============================================
class CHitCameraEffectSevere :public CHitCameraEffect
{
public:
	static const std::string TEXTURE_NAME;	//�y�x�e�N�X�`���̖��O

	CHitCameraEffectSevere(int nPriority = PRIORITY);
	~CHitCameraEffectSevere() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif // _HIT_CAMERA_EFFECT_H_