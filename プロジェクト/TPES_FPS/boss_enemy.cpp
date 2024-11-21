//=============================================
//
//ボスの敵の処理[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CBossEnemy::CBossEnemy(int nPriority)
{
	if (m_pMove == nullptr)
	{
		m_pMove = new CBossWandering;
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
}

//=============================================
//初期化
//=============================================
HRESULT CBossEnemy::Init()
{
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
	CEnemy::Update();
	Motion(NUM_PARTS); //モーション処理
}

//=============================================
//描画
//=============================================
void CBossEnemy::Draw()
{
	CEnemy::Draw();
}
