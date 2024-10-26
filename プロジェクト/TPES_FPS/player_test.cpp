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

	m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f));

	//ムーブ値代入
	SetMove(move);

	//パーツ読み込み
	Load_Parts("data\\Motion.txt",NUM_PARTS);

	SetMotion(MOTION_NEUTRAL, NUM_PARTS);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer_test::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();

}

//=============================================
//更新
//=============================================
void CPlayer_test::Update()
{
	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	CCharacter::Update();

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

		//重力処理
		Gravity();

		if (GetFinish())
		{
			//入力処理
			Input();
		}

		//位置取得
		D3DXVECTOR3 pos = GetPos();

		//過去の位置
		D3DXVECTOR3 oldpos = GetOldPos();

		//移動量取得
		D3DXVECTOR3 move = GetMove();

		//移動量を更新(減速）
		move.x += (0.0f - move.x) * DAMPING_COEFFICIENT;
		move.y += (0.0f - move.y) * DAMPING_COEFFICIENT;
		move.z += (0.0f - move.z) * DAMPING_COEFFICIENT;

		//移動量代入
		SetMove(move);

		//過去の位置に今の位置を代入
		oldpos = pos;

		//過去の位置代入
		SetOldPos(oldpos);

		//移動量追加
		pos += move;

		//座標を更新
		SetPos(pos);

		//最大最小値取得
		D3DXVECTOR3 minpos = GetMinPos();
		D3DXVECTOR3 maxpos = GetMaxPos();

		//ブロックとの接触処理
		HitBlock();

		//床との接触処理
		HitField();

		//ゲームの状態取得
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetLaunding())
		{//着地してるなら
			//ジャンプ数リセット
			m_nJumpCnt = 0;
		}

		if (pos.y < DEADZONE_Y)
		{//リスポーン処理
			ReSpawn();
		}


		//カメラ情報取得
		CCamera* pCamera = CManager::GetCamera();

		m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));

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

	//親クラスの移動
	CCharacter::Move(D3DXVECTOR3(vecDirection.x,0.0f, vecDirection.z), rotMoveY, Motion);

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
	////移動量代入
	//SetMove(move);
	if (combat_state != CCharacter::COMBAT_STATE::STATE_ATTACK &&pMouse->GetPress(1))
	{//アタック状態じゃなくマウスが押されてる間は
		//ステートをアタック状態に
		combat_state = CCharacter::COMBAT_STATE::STATE_ATTACK;
	}

	if (combat_state == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetRelease(1))
	{//アタック状態じゃなくマウスが離されたら
		//ステートをノーマル状態に
		combat_state = CCharacter::COMBAT_STATE::STATE_NORMAL;
	}

	SetCombat_State(combat_state);

	if (GetCombat_State() == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetTrigger(0))
	{//アタック状態だったら
		//位置取得
		D3DXVECTOR3 pos = GetPos();
		//弾発射
		ShotBullet(D3DXVECTOR3(m_Raticle->GetPos()), 4.0f, D3DXVECTOR3(5.0f, 5.0f, 0.0f), 1, CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL);
	}


}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer_test::DebugPos()
{
	LPD3DXFONT pFont = CManager::GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z,GetMove().x,GetMove().y,GetMove().z);
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}
