//=============================================
//
//通常の敵の処理[normal_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy.h"
#include "normal_enemy_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority)
{
	if (m_pMove == nullptr)
	{
		m_pMove = new CNormalMove;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CNormalAttack;
	}
}

//=============================================
//デストラクタ
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CNormalEnemy::Init()
{
	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	Load_Parts("data\\Motion.txt");
	SetLife(DEFAULT_LIFE);
	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CNormalEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CNormalEnemy::Update()
{
	CEnemy::Update();
	Motion(NUM_PARTS); //モーション処理
}

//=============================================
//描画
//=============================================
void CNormalEnemy::Draw()
{
	CEnemy::Draw();
}
