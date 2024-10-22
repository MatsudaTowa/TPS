//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
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
#include "player_test.h"
#include "enemy_test.h"

const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//プレイヤー
CPlayer*CGame::m_pPlayer = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//イニシャライザーでプライオリティ設定、エディットしてない状態に変更
	//読み込むブロックの情報初期化
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	//ブロック生成
	LoadBlock(&CGame::BLOCK_FILE);

	//地面生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//プレイヤー生成
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//プレイヤー生成
	CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
	CEnemy_test* pEnemy_test = CEnemy_test::Create(D3DXVECTOR3(-850.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	m_GameState = GAME_STATE_NORMAL;
	
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}
	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
	}

}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//プレイヤー取得
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}

//=============================================
//ブロック読み込み
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[＝]読み込み用
	int nNumBlock; //ブロックの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//エネミー生成
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
