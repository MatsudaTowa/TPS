//=============================================
//
//ウェーブ処理[wave.h]
//Auther Matsuda Towa
//
//=============================================
#include "wave.h"
#include "enemy_test.h"
#include "manager.h"
#include "wave_one.h"
#include "wave_two.h"
#include "wave_three.h"
#include "wave_boss.h"
#include "wave_result.h"

CWave::WAVE CWave::m_CurrentWave = WAVE::NONE;
CWave::WAVE CWave::m_next = WAVE::NONE;
const char* CWave::m_ResultFile = nullptr;

//=============================================
//コンストラクタ
//=============================================
CWave::CWave()
{
}

//=============================================
//デストラクタ
//=============================================
CWave::~CWave()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave::Init()
{
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave::Uninit()
{
}

//=============================================
//更新
//=============================================
void CWave::Update()
{
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave)
{
	// インスタンス生成
	CWave* pWave = new CWave;

	// 条件分岐
	switch (wave)
	{
	case WAVE::ONE: // ウェーブ1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //ウェーブ2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // ウェーブ3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //ウェーブboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Boss;
		break;
	default:
		break;
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave, WAVE next_wave,const char* ResultFile)
{
	// インスタンス生成
	CWave* pWave = new CWave;

	m_next = next_wave;

	m_ResultFile = ResultFile;

	// 条件分岐
	switch (wave)
	{
	case WAVE::ONE: // ウェーブ1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //ウェーブ2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // ウェーブ3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //ウェーブboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//現在のウェーブを取得
//=============================================
CWave::WAVE CWave::GetCurrentWave()
{
	return m_CurrentWave;
}

//=============================================
//ブロックをロード
//=============================================
void CWave::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
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
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
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

//=============================================
//エネミーをロード
//=============================================
void CWave::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumEnemy; //エネミーの数

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

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//エネミー生成
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}

void CWave::SetWaveScore(int nScore)
{
	m_nScore = nScore;
}

