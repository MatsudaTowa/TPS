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
#include "colision.h"

class CManager
{
public:
	static const int NUM_RESULT_FILE = 4;
	static const std::string RESULT_SCORE_FILE[NUM_RESULT_FILE]; //���U���g�̃t�@�C���l�[��

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�V�[���ݒ�
	void SetMode(CScene::MODE mode);

	static CManager* GetInstance()
	{
		static CManager instance; //�ÓI�C���X�^���X
		return &instance;
	}

	//�V�[���擾
	CScene* GetScene();
	//�����_���[�擾
	CRenderer*GetRenderer();
	//�L�[�{�[�h���擾
	CInputKeyboard* GetKeyboard();
	//�}�E�X���擾
	CInputMouse* GetMouse();
	//pad���擾
	CInputPad* GetPad();
	//�J�����擾
	CCamera* GetCamera();
	//���C�g�擾
	CLight* GetLight();
	//�e�N�X�`���擾
	CTexture* GetTexture();
	//���f���擾
	CModel* GetModel();
	//�T�E���h�擾
	CSound* GetSound();
	//�t�F�[�h�擾
	CFade* GetFade();
	
	CColision* GetColision();

	CFade* m_pFade;

	static void ExportScoreReset(const std::string* pFileName); //�X�R�A��0�����o��

private:

	CScene* m_pScene; //���݂̃V�[��
	//static CFade* m_pFade;
	CRenderer* m_pRenderer;
	CInputKeyboard* m_pKeyboard;
	CInputMouse* m_pMouse;
	CInputPad* m_pPad;
	CCamera* m_pCamera;
	CLight* m_pLight;
	CTexture* m_pTexture;
	CModel* m_pModel;
	CSound* m_pSound;
	CColision* m_pColision;
};

#endif