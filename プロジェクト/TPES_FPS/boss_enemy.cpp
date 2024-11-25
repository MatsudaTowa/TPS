//=============================================
//
//ボスの敵の処理[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

const float CBossEnemy::FIND_PLAYER_DISTANCE = 500.0f; //この値までだったら追いかける
const float CBossEnemy::LOST_PLAYER_DISTANCE = 800.0f; //この値以上だったら見失う

//=============================================
//コンストラクタ
//=============================================
CBossEnemy::CBossEnemy(int nPriority)
{
	m_pBossState = nullptr;

	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CBossAttack;
	}
}

//=============================================
//デストラクタ
//=============================================
CBossEnemy::~CBossEnemy()
{
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
	}
	if (m_pWandering != nullptr)
	{
		delete m_pWandering;
	}
	if (m_pChase != nullptr)
	{
		delete m_pChase;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CBossEnemy::Init()
{
	if (m_pBossState == nullptr)
	{
		m_pBossState = new CChaseState;
	}
	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	SetLife(DEFAULT_LIFE);
	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBossEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CBossEnemy::Update()
{
	//TODO:無駄な処理多い気が...
	m_pBossState->Chase(this);

	m_pBossState->Wandering(this);

	CEnemy::Update();
	Motion(NUM_PARTS); //モーション処理
}

//=============================================
//描画
//=============================================
void CBossEnemy::Draw()
{
	m_pWandering->DrawDebug();
	CEnemy::Draw();
}

//=============================================
//ボスの状態切り替え
//=============================================
void CBossEnemy::ChangeState(CBossState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
		m_pBossState = state;
	}
}
