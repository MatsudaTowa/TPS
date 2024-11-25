//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"
#include "wave.h"
#include "game.h"

//�X�R�A�ݒ�
CScore* CResult::m_pScore = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CResult::CResult()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CResult::~CResult()
{
}

//=============================================
//������
//=============================================
HRESULT CResult::Init()
{
    //�X�R�A������
    if (m_pScore == nullptr)
    {
        m_pScore = new CScore;

        m_pScore->Init();
    }

    CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f));
  
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CResult::Uninit()
{
    for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
    {
        CManager::ExportScoreReset(&CManager::RESULT_SCORE_FILE[nCnt]);
    }
    if (m_pScore != nullptr)
    {
        m_pScore->Uninit();
        m_pScore = nullptr;
    }

    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CResult::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();

    if (m_pScore != nullptr)
    {
        m_pScore->Update();
    }

    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//�`��
//=============================================
void CResult::Draw()
{
}
