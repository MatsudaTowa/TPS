//=============================================
//
//ゲーム[game.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "dash_effect.h"
#include "active_player.h"

//ウェーブ
CWave* CGame::m_pWave = nullptr;
//=============================================
//コンストラクタ
//=============================================
CGame::CGame():
m_nResultDelay(INT_ZERO),	//リザルトの遷移ディレイ
m_next_wave(),				//次のウェーブ格納変数
m_nPauseCnt(INT_ZERO),		//ポーズ可能変数
m_pState(nullptr)			//ステートポインタ
{
	//読み込むブロックの情報初期化
	m_LoadBlock.pos = VEC3_RESET_ZERO;
	m_LoadBlock.rot = VEC3_RESET_ZERO;
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	if (m_pState == nullptr)
	{
		m_pState = new CNormal;
	}

	if (m_pWave == nullptr)
	{
		m_pWave = new CWave;
		m_pWave->Init();
	}

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		m_pWave = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	if (m_nPauseCnt <= PAUSE_POSSIBLE_FLAME)
	{
		++m_nPauseCnt;
	}
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Pause(this);
	}
}

//=============================================
//死んだ数だけスコアマイナス
//=============================================
void CGame::ApplyDeathPenalty()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();
			
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなかったら
			//プレイヤーを探し続ける
			continue;
		}

		CActivePlayer* pPlayer = dynamic_cast<CActivePlayer*>(pObj);

		for (int nCnt = 0; nCnt < pPlayer->GetDeathCnt(); nCnt++)
		{
			CScore* pScore = CWave::GetScore();

			if (pScore->GetScore() > INT_ZERO)
			{
				pScore->AddScore(DEATH_PENALTY);

				if (pScore->GetScore() <= INT_ZERO)
				{//0を下回ったら
					//スコア0に
					pScore->SetScore(INT_ZERO);
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//ステート変更
//=============================================
void CGame::ChangeState(CGameState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
//オブジェクトの更新を行うか決定
//=============================================
void CGame::UpdateObjectDecision(bool isActive)
{
	for (int i = 0; i < CObject::PRI_MAX; ++i)
	{
		for (int j = 0; j < CObject::MAX_OBJECT; ++j)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(i, j);	//先頭取得

			if (pObj == nullptr)
			{
				continue;
			}

			if (pObj->GetisActive() != isActive)
			{
				pObj->SetisActive(isActive);
			}
		}
	}
}


//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave);
	}
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave, CWave::WAVE next_wave,const char* ResultFile)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave, next_wave, ResultFile);
	}
}