//=============================================
//
//3DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
//#include "fade.h"

const std::string CManager::RESULT_SCORE_FILE[NUM_RESULT_FILE] =
{
	"data\\FILE\\score\\wave_one_score.bin",
	"data\\FILE\\score\\wave_two_score.bin",
	"data\\FILE\\score\\wave_three_score.bin",
	"data\\FILE\\score\\wave_boss_score.bin",
};

//=============================================
//�R���X�g���N�^
//=============================================
CManager::CManager():m_pCamera(nullptr),
	m_pColision(nullptr),
	m_pFade(nullptr),
	m_pKeyboard(nullptr),
	m_pLight(nullptr),
	m_pModel(nullptr),
	m_pMouse(nullptr),
	m_pPad(nullptr),
	m_pRenderer(nullptr),
	m_pScene(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr)
{
	
}

//=============================================
//�f�X�g���N�^
//=============================================
CManager::~CManager()
{
}

//=============================================
//������
//=============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	//������������
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd,bWindow);
	}
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//�L�[�{�[�h�̏���������
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CInputMouse();

		//�}�E�X�̏���������
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	if (m_pPad == nullptr)
	{
		m_pPad = new CInputPad();

		//�}�E�X�̏���������
		if (FAILED(m_pPad->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�J��������
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}

	if (m_pScene == nullptr)
	{
		m_pScene =new CScene();
		m_pScene->Init();

	}

	//���C�g����
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight();
		m_pLight->Init();
	}

	//�e�N�X�`������
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture();
	}

	//���f������
	if (m_pModel == nullptr)
	{
		m_pModel = new CModel();
	}

	//�T�E���h����
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound();
		m_pSound->InitSound(hWnd);

	}

	//�����蔻�萶��
	if (m_pColision == nullptr)
	{
		m_pColision = new CColision();
	}

	//�ŏ��̃V�[���ݒ�
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	//m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	SetMode(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//=============================================
//�I������
//=============================================
void CManager::Uninit()
{
	for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
	{
		ExportScoreReset(&RESULT_SCORE_FILE[nCnt]);
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//�����蔻��j��
	if (m_pColision != nullptr)
	{
		delete m_pColision;
		m_pColision = nullptr;
	}


	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�L�[�{�[�h�̏I������
	m_pKeyboard->Uninit();
	//�}�E�X�̏I������
	m_pMouse->Uninit();
	//Pad�̏I������
	m_pPad->Uninit();

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	CObject::ReleaseAll();

}

//=============================================
//�X�V����
//=============================================
void CManager::Update()
{
	//�X�V����
	m_pRenderer->Update();
	m_pCamera->Update();
	m_pKeyboard->Update();
	m_pMouse->Update();
	m_pPad->Update();

	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	//�V�[���̍X�V
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}

	CObject::UpdateAll();

}

//=============================================
//�`�揈��
//=============================================
void CManager::Draw()
{
	//�`�揈��
	m_pRenderer->Draw();

	//�V�[���̕`��
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}

}

//=============================================
//�X�R�A��0�����o��
//=============================================
void CManager::ExportScoreReset(const std::string* pFileName)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "wb");

	int nReset = 0;

	if (pFile != NULL)
	{
		fwrite(&nReset, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//=============================================
//�V�[���ݒ�
//=============================================
void CManager::SetMode(CScene::MODE mode)
{
	//�V�[���I��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�V�[���؂�ւ�
	if (m_pScene == nullptr)
	{
		m_pScene = CScene::Create(mode);
	}
}

//=============================================
//�V�[��
//=============================================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=============================================
//�����_���[�擾
//=============================================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================
//�L�[�{�[�h���擾
//=============================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================
//pad���擾
//=============================================
CInputMouse* CManager::GetMouse()
{
	return m_pMouse;
}

//=============================================
//�}�E�X���擾
//=============================================
CInputPad* CManager::GetPad()
{
	return m_pPad;
}

//=============================================
//�J�����擾
//=============================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================================
//���C�g�擾
//=============================================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//=============================================
//�e�N�X�`���擾
//=============================================
CTexture* CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================
//���f���擾
//=============================================
CModel* CManager::GetModel()
{
	return m_pModel;
}

//=============================================
//�T�E���h�擾
//=============================================
CSound* CManager::GetSound()
{
	return m_pSound;
}

//=============================================
//�t�F�[�h�擾
//=============================================
CFade* CManager::GetFade()
{
	return m_pFade;
}

//=============================================
//�����蔻��擾
//=============================================
CColision* CManager::GetColision()
{
	return m_pColision;
}

