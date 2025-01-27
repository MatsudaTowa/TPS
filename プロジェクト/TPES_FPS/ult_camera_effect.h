//=============================================
//
//�E���g���̃J�����G�t�F�N�g�uult_camera_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ULT_CAMERA_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _ULT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�E���g���̃J�����G�t�F�N�g�N���X
//=============================================
class CUltCameraEffect :public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int PRIORITY = 25; //�`�揇

	CUltCameraEffect(int nPriority = PRIORITY);
	~CUltCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CUltCameraEffect* Create(D3DXVECTOR3 pos);

	void SubAlpha();

	float& GetAlpha()
	{
		return m_alpha;
	}
private:
	float m_alpha; //�A���t�@�l
};

#endif // _ULT_CAMERA_EFFECT_H_