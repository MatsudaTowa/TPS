//=============================================
//
//3DTemplate[scene.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "test.h"
#include "result.h"
#include "manager.h"

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
    // �C���X�^���X����
    CScene* pScene = new CScene;

    // ��������
    switch (mode)
    {
    case MODE_TITLE: // �^�C�g��

        delete pScene;
        pScene = new CTitle;
        break;
    
    case MODE_TEST: //�e�X�g
        delete pScene;
        pScene = new CTest;
        break;

    case MODE_GAME: // �Q�[��

        delete pScene;
        pScene = new CGame;
        break;
    case MODE_RESULT: //���U���g

        delete pScene;
        pScene = new CResult;
        break;
    default:
        break;
    }

    if (pScene != nullptr)
    {
        pScene->m_Mode = mode;
    }
    //���̃V�[���̏�����
    pScene->Init();

    return pScene;
}

//=============================================
//�V�[���̎擾
//=============================================
CScene::MODE CScene::GetSceneMode()
{
    return m_Mode;
}

