//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(������)�uhit_camera_effect_moderate.h�v
// Author���c�i�v
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_MODERATE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _HIT_CAMERA_EFFECT_MODERATE_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//�q�b�g���̃J�����G�t�F�N�g�N���X
//=============================================
class CHitCameraEffectModerate :public CHitCameraEffect
{
public:
	static const std::string TEXTURE_NAME;	//�y�x�e�N�X�`���̖��O

	CHitCameraEffectModerate(int nPriority = PRIORITY);
	~CHitCameraEffectModerate() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif // _HIT_CAMERA_EFFECT_H_