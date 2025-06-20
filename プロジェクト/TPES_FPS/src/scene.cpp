//=============================================
//
//�V�[��[scene.cpp]
//Author Matsuda Towa
//
//=============================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "test.h"
#include "result.h"
#include "manager.h"
#include "tutorial.h"

//���[�h������
CScene::MODE CScene::m_Mode = CScene::MODE::MODE_TITLE;

//=============================================
//�R���X�g���N�^
//=============================================
CScene::CScene()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CScene::~CScene()
{
}

//=============================================
//������
//=============================================
HRESULT CScene::Init()
{
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CScene::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CScene::Update()
{
}

//=============================================
//�`��
//=============================================
void CScene::Draw()
{
}

//=============================================
//����
//=============================================
CScene* CScene::Create(MODE mode)
{
    CManager::GetInstance()->GetCamera()->SetActive(true);

    // �C���X�^���X����
    CScene* pScene = nullptr;

    // ��������
    switch (mode)
    {
    case MODE_TITLE: // �^�C�g��
        pScene = new CTitle;
        break;
    
    case MODE_TEST: //�e�X�g
        pScene = new CTest;
        break;

    case MODE_TUTORIAL: //�`���[�g���A��
        pScene = new CTutorial;
        break;

    case MODE_GAME: // �Q�[��

        pScene = new CGame;
        break;
    case MODE_RESULT: //���U���g
        pScene = new CResult;
        break;
    default:
        assert(true);
        break;
    }

    if (pScene != nullptr)
    {
        pScene->m_Mode = mode;
    }
    //���̃V�[���̏�����
    pScene->Init();

    CManager::GetInstance()->GetModel()->Unload();

    return pScene;
}

//=============================================
//�V�[���̎擾
//=============================================
CScene::MODE CScene::GetSceneMode()
{
    return m_Mode;
}

