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
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CNormalAttack;
	}
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CEnemyConfusion;
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

	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = CEnemy_Ammo_UI::Create({m_apModel[1]->GetMtxWorld()._41 + 10.0f,m_apModel[1]->GetMtxWorld()._42 + 40.0f,m_apModel[1]->GetMtxWorld()._43},
		{5.0f,10.0f,0.0f});
	}

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
	m_pAmmoUI->SetPos({ m_apModel[1]->GetMtxWorld()._41 + 10.0f,m_apModel[1]->GetMtxWorld()._42 + 40.0f,m_apModel[1]->GetMtxWorld()._43 });
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
