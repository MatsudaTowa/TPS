//=============================================
//
//3DTemplate[maneger.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�V�[���ݒ�
	static void SetMode(CScene::MODE mode);

	//�����_���[�擾
	static CScene* GetScene();
	//�����_���[�擾
	static CRenderer*GetRenderer();
	//�L�[�{�[�h���擾
	static CInputKeyboard* GetKeyboard();
	//�}�E�X���擾
	static CInputMouse* GetMouse();
	//�}�E�X���擾
	static CInputPad* GetPad();
	//�J�����擾
	static CCamera* GetCamera();
	//���C�g�擾
	static CLight* GetLight();
	//�e�N�X�`���擾
	static CTexture* GetTexture();
	//���f���擾
	static CModel* GetModel();
	//�T�E���h�擾
	static CSound* GetSound();
	//�t�F�[�h�擾
	static CFade* GetFade();

	static CFade* m_pFade;

private:
	static CScene* m_pScene; //���݂̃V�[��
	//static CFade* m_pFade;
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CInputMouse* m_pMouse;
	static CInputPad* m_pPad;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CTexture* m_pTexture;
	static CModel* m_pModel;
	static CSound* m_pSound;
};

#endif