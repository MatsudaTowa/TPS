//=============================================
//
//�X���[�N�̃J�����G�t�F�N�g�uhit_camera_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SMOKE_CAMERA_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SMOKE_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�X���[�N�̃J�����G�t�F�N�g�N���X
//=============================================
class CSmokeCameraEffect :public CObject2D
{
public:
	static const int PRIORITY = 28; //�`�揇

	CSmokeCameraEffect(int nPriority = PRIORITY);
	~CSmokeCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CSmokeCameraEffect* Create();

	void SubAlpha();

	inline float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	static constexpr float FADE_VALUE = 0.01f;  //�A���t�@�l������

	float m_alpha; //�A���t�@�l
};

#endif // _HIT_CAMERA_EFFECT_H_