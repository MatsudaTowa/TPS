//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "wave.h"
#include "game.h"

//���U���g�t�@�C���p�X
const char* CResult::WAVE_RESULT_FILE[CManager::NUM_RESULT_FILE]
{
    "data\\FILE\\score\\wave_one_score.bin",
    "data\\FILE\\score\\wave_two_score.bin",
    "data\\FILE\\score\\wave_three_score.bin",
    "data\\FILE\\score\\wave_boss_score.bin"
};

//�\������X�R�A�̈ʒu
const D3DXVECTOR3 CResult::SCORE_POS[CManager::NUM_RESULT_FILE + 1]
{
    {1000.0f,170.0f,0.0f},
    {1000.0f,270.0f,0.0f},
    {1000.0f,370.0f,0.0f},
    {1000.0f,470.0f,0.0f}, 
    {1100.0f,620.0f,0.0f}, 
};

const D3DXVECTOR2 CResult::SCORE_SIZE[2]
{
    { 40.0f, 50.0f },
    { 60.0f, 70.0f },
};

const float CResult::DIGIT_SHIFT[2]
{
    60.0f,
    90.0f,
};

//=============================================
//�R���X�g���N�^
//=============================================
CResult::CResult():
m_pScore()
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
    CScene::Init();

    for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE + 1; nCnt++)
    {
        //�X�R�A������
        if (m_pScore[nCnt] == nullptr)
        {
            m_pScore[nCnt] = new CScore;

            m_pScore[nCnt]->SetPos(SCORE_POS[nCnt]);

            if (nCnt == 4)
            {//�ŏI�X�R�A�����傫���\��
                m_pScore[nCnt]->SetSize(SCORE_SIZE[1]);
                m_pScore[nCnt]->SetDigitShift(DIGIT_SHIFT[1]);
            }
            else
            {
                m_pScore[nCnt]->SetSize(SCORE_SIZE[0]);
                m_pScore[nCnt]->SetDigitShift(DIGIT_SHIFT[0]);
            }

            m_pScore[nCnt]->Init();
        }
    }

    //���܂ł̃X�R�A��ǂݍ���
    for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
    {
        if (m_pScore[nCnt] != nullptr)
        {
            m_pScore[nCnt]->AddScore(LoadScore(WAVE_RESULT_FILE[nCnt]));
        }

        m_pScore[4]->AddScore(LoadScore(WAVE_RESULT_FILE[nCnt]));
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
    {//���܂ł̃f�[�^�폜
        CManager::ExportScoreReset(&CManager::RESULT_SCORE_FILE[nCnt]);
    }
    for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE + 1; nCnt++)
    {
        if (m_pScore[nCnt] != nullptr)
        {
            m_pScore[nCnt]->Uninit();
            m_pScore[nCnt] = nullptr;
        }
    }

    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CResult::Update()
{
    //�e�C���v�b�g�擾
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();
    CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

    for (int nCnt = 0; nCnt < 5; nCnt++)
    {
        if (m_pScore[nCnt] != nullptr)
        {
            m_pScore[nCnt]->Update();
        }
    }

    if (pKeyboard->GetTrigger(DIK_RETURN) 
        || pMouse->GetTrigger(0)
        || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        //�^�C�g���ɖ߂�
        CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//�`��
//=============================================
void CResult::Draw()
{
}

//=============================================
//�X�R�A�ǂݍ���
//=============================================
int CResult::LoadScore(const char* FileName)
{
    //�t�@�C���̓ǂݍ���
    FILE* pFile = fopen(FileName, "rb");

    int nScore = 0; //�Ԃ��X�R�A

    if (pFile != NULL)
    {
        //�X�R�A�̓ǂݍ���
        fread(&nScore, sizeof(int), 1, pFile);

        //�t�@�C�������
        fclose(pFile);
    }

    else
    {
        return 0;
    }

    return nScore;
}
