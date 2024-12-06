//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g�uhit_camera_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _HIT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�̗͕\���N���X
//=============================================
class CHitCameraEffect:public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int PRIORITY = 30; //�`�揇

	CHitCameraEffect(int nPriority = PRIORITY);
	~CHitCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CHitCameraEffect* Create(D3DXVECTOR3 pos);

	void SubAlpha();

	float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	float m_alpha; //�A���t�@�l
};

#endif // _HIT_CAMERA_EFFECT_H_