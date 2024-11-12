//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_test.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"

//通常の移動速度
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//ジャンプ回数
const int CPlayer_test::MAX_JUMPCNT = 2;

//プレイヤーをリスポーンされる座標
const float CPlayer_test::DEADZONE_Y = -100.0f;

CAmmo_UI* CPlayer_test::m_pAmmoUI = nullptr;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer_test::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer_test::m_pMesh = nullptr;

DWORD CPlayer_test::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0),m_Raticle()
{//イニシャライザーでメンバ変数初期化
	if (m_pMove == nullptr)
	{
		m_pMove = new CDush;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CPlayerAttack;
	}
}

//=============================================
//デストラクタ
//=============================================
CPlayer_test::~CPlayer_test()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer_test::Init()
{
	CCharacter::Init();

	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	//残弾数初期化
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();
	}

	m_Raticle = nullptr;

	m_bRelorad = false;

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetModel();
	}

	//カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();

	//ムーブ値代入
	SetMove(move);

	//パーツ読み込み
	Load_Parts("data\\Motion.txt");

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer_test::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}

	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();

}

//=============================================
//更新
//=============================================
void CPlayer_test::Update()
{
	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	CCharacter::Update();

	if (m_bRelorad == true)
	{//リロード中だったら
		m_bRelorad = m_pGun->Reload(); //リロードし終わったらfalseが返ってくる
	}

	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetAmmo_UI(m_pGun->GetAmmo());
	}

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//状態のカウント数取得
			int nStateCnt = GetStateCnt();

			//ステート変更カウント進める
			nStateCnt++;

			//ステートカウント代入
			SetStateCnt(nStateCnt);
		}

		if (GetFinish())
		{
			//入力処理
			Input();
		}

		//カメラ情報取得
		CCamera* pCamera = CManager::GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		}

		//どっち向いてるか取得
		bool bWay = GetWay();

		Motion(NUM_PARTS); //モーション処理
	}
}

//=============================================
//描画
//=============================================
void CPlayer_test::Draw()
{
	CInputMouse* pMouse = CManager::GetMouse();
	pMouse->Debug();
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw(NUM_PARTS);
	//プレイヤーのデバッグ表示
	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	CPlayer_test* pPlayer = new CPlayer_test;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	pPlayer->Init(); //初期化処理

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer_test::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//HPが残ってたら
		nLife -= nDamage;

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		//終了
		Uninit();
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
//リスポーン
//=============================================
void CPlayer_test::ReSpawn()
{
	////自分自身のpos取得
	//D3DXVECTOR3 PlayerPos = GetPos();

	//PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	////pos代入
	//SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CPlayer_test::Input()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputMouse* pMouse = CManager::GetMouse();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	COMBAT_STATE state = CCharacter::GetCombat_State();
	if (state != COMBAT_STATE::STATE_ATTACK)
	{
		switch (pCameraType)
		{//サイドビューの時は横にしか動かないように設定
		case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
			if (pKeyboard->GetPress(DIK_A))
			{
				vecDirection.x -= 1.0f;
				bWay = false;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
			if (pKeyboard->GetPress(DIK_A))
			{
				vecDirection.x -= 1.0f;
				bWay = false;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		default:
			if (pKeyboard->GetPress(DIK_W))
			{
				vecDirection.z += 1.0f;
			}
			if (pKeyboard->GetPress(DIK_S))
			{
				vecDirection.z -= 1.0f;
			}
			if (pKeyboard->GetPress(DIK_A))
			{
				vecDirection.x -= 1.0f;
				bWay = false;
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		}
	}

	float rotMoveY = CManager::GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		Motion = MOTION_NEUTRAL;
	}
	else
	{	
		Motion = MOTION_MOVE;
	}

	//移動処理
	m_pMove->Move(D3DXVECTOR3(vecDirection.x, 0.0f, vecDirection.z), rotMoveY,this,Motion);

	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			//親クラスのジャンプ処理
			CCharacter::Jump();
			m_nJumpCnt++; //ジャンプ数加算
		}
	}

	CCharacter::COMBAT_STATE combat_state = GetCombat_State();
	CCamera* pCamera = CManager::GetCamera();
	////移動量代入
	//SetMove(move);
	if (combat_state != CCharacter::COMBAT_STATE::STATE_ATTACK &&pMouse->GetPress(1))
	{//アタック状態じゃなくマウスが押されてる間は
		//ステートをアタック状態に
		combat_state = CCharacter::COMBAT_STATE::STATE_ATTACK;

		if (m_Raticle == nullptr)
		{//使われていなかったら
			m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		}
	}

	if (combat_state == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetRelease(1))
	{//アタック状態じゃなくマウスが離されたら
		//ステートをノーマル状態に
		combat_state = CCharacter::COMBAT_STATE::STATE_NORMAL;

		if(m_Raticle != nullptr)
		{//使われていたら
			m_Raticle->Uninit();
			m_Raticle = nullptr;
		}
	}

	SetCombat_State(combat_state);

	if (GetCombat_State() == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetPress(0))
	{//アタック状態だったら
		if (m_pAttack != nullptr)
		{
			m_pAttack->Attack(D3DXVECTOR3(m_Raticle->GetPos()), D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -CAssultRifle::DEFAULT_AR_BULLET_SPEED,
				sinf(pCamera->GetRot().x + D3DX_PI)* CAssultRifle::DEFAULT_AR_BULLET_SPEED,
				cosf(pCamera->GetRot().y + D3DX_PI) * -CAssultRifle::DEFAULT_AR_BULLET_SPEED),
				D3DXVECTOR3(1.5f, 1.5f, 1.5f), 1, CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, m_pGun, this);
		}
	}
	if (pMouse->GetRelease(0))
	{
		m_pGun->m_nRateCnt = 0;
	}

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//リロード
			m_bRelorad = true;
		}
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer_test::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n弾数:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
