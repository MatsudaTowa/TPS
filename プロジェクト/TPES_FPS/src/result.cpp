//=============================================
//
//結果[result.cpp]
//Author Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "wave.h"
#include "game.h"

//リザルトファイルパス
const std::string CResult::WAVE_RESULT_FILE[CManager::NUM_RESULT_FILE]
{
    "data\\FILE\\score\\wave_one_score.bin",
    "data\\FILE\\score\\wave_two_score.bin",
    "data\\FILE\\score\\wave_three_score.bin",
    "data\\FILE\\score\\wave_boss_score.bin"
};

//表示するスコアの位置
const D3DXVECTOR3 CResult::SCORE_POS[CManager::NUM_RESULT_FILE + 1]
{
    {1000.0f,170.0f,0.0f},
    {1000.0f,270.0f,0.0f},
    {1000.0f,370.0f,0.0f},
    {1000.0f,470.0f,0.0f}, 
    {1100.0f,620.0f,0.0f}, 
};

//スコアサイズ
const D3DXVECTOR2 CResult::SCORE_SIZE[2]
{
    { 40.0f, 50.0f },
    { 60.0f, 70.0f },
};

//桁ずらし
const float CResult::DIGIT_SHIFT[2]
{
    60.0f,
    90.0f,
};

//=============================================
//コンストラクタ
//=============================================
CResult::CResult():
m_pScore()      //スコアのポインター
{
}

//=============================================
//デストラクタ
//=============================================
CResult::~CResult()
{
}

//=============================================
//初期化
//=============================================
HRESULT CResult::Init()
{
    //初期化
    CScene::Init();

    for (int nCnt = INT_ZERO; nCnt < CManager::NUM_RESULT_FILE + 1; nCnt++)
    {
        //スコア初期化
        if (m_pScore[nCnt] == nullptr)
        {
            m_pScore[nCnt] = new CScore;

            m_pScore[nCnt]->SetPos(SCORE_POS[nCnt]);

            if (nCnt == CManager::NUM_RESULT_FILE)
            {//最終スコアだけ大きく表示
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

    //今までのスコアを読み込み
    for (int nCnt = INT_ZERO; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
    {
        if (m_pScore[nCnt] != nullptr)
        {
            m_pScore[nCnt]->AddScore(LoadScore(WAVE_RESULT_FILE[nCnt]));
        }

        m_pScore[CManager::NUM_RESULT_FILE]->AddScore(LoadScore(WAVE_RESULT_FILE[nCnt]));
    }

    CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF, 0.0f));
  
    return S_OK;
}

//=============================================
//終了
//=============================================
void CResult::Uninit()
{
    for (int nCnt = INT_ZERO; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
    {//今までのデータ削除
        CManager::ExportScoreReset(&CManager::RESULT_SCORE_FILE[nCnt]);
    }
    for (int nCnt = INT_ZERO; nCnt < CManager::NUM_RESULT_FILE + 1; nCnt++)
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
//更新
//=============================================
void CResult::Update()
{
    //各インプット取得
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

    for (int nCnt = INT_ZERO; nCnt < CManager::NUM_RESULT_FILE + 1; nCnt++)
    {
        if (m_pScore[nCnt] != nullptr)
        {
            m_pScore[nCnt]->Update();
        }
    }

    if (pKeyboard->GetTrigger(DIK_RETURN) 
        || pMouse->GetTrigger(0))
    {
        //タイトルに戻る
        CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//描画
//=============================================
void CResult::Draw()
{
}

//=============================================
//スコア読み込み
//=============================================
int CResult::LoadScore(const std::string& FileName)
{
    int nScore = INT_ZERO; //返すスコア

    //ファイルの読み込み
    std::ifstream File(FileName, std::ios::binary);

    //ファイルが開かなかったら関数を抜ける
    if (!File.is_open())
    {
        return 0;
    }

    File.read(reinterpret_cast<char*>(&nScore), sizeof(int));

    return nScore;
}
