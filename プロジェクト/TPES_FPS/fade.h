//=============================================
//
//�t�F�[�h����[fade.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _FADE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FADE_H_
#include "main.h"
#include "scene.h"
#include "object2D.h"

//fade�N���X
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0, //�������Ă��Ȃ����
		FADE_IN, //�t�F�[�h�C��
		FADE_OUT, //�t�F�[�h�A�E�g
		FADE_MAX,
	}FADE;

	//static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int FADE_PRIORITY = 98;  //�`�揇
	static const float FADE_VALUE;  //�A���t�@�l������

	CFade(int nPriority = FADE_PRIORITY);
	~CFade()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetFade(CScene::MODE modeNext);

	//static FADE GetFade(void);
	float FadeColor(void);
	static CFade* Create(D3DXVECTOR3 pos);
private:
	//static LPDIRECT3DTEXTURE9 m_pTexture;
	FADE m_fade;
	CScene::MODE m_fademode;
	float m_colorFade;
};
#endif