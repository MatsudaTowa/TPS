//=============================================
//
//3DTemplate[enemy_test.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_test.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"

//通常の移動速度
const float CEnemy_test::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CEnemy_test::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CEnemy_test::DEFAULT_JUMP = 25.0f;

//ジャンプ回数
const int CEnemy_test::MAX_JUMPCNT = 2;

//プレイヤーをリスポーンされる座標
const float CEnemy_test::DEADZONE_Y = -100.0f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CEnemy_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy_test::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy_test::m_pMesh = nullptr;

DWORD CEnemy_test::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CEnemy_test::CEnemy_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0), m_apModel()
, m_Motion()
{//イニシャライザーでメンバ変数初期化

}

//=============================================
//デストラクタ
//=============================================
CEnemy_test::~CEnemy_test()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_test::Init()
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

	//ムーブ値代入
	SetMove(move);

	Load_Parts("data\\Motion.txt", NUM_PARTS);

	m_Motion = CEnemy_test::Motion_Type::MOTION_MAX; //ニュートラルに設定

	SetMotion(MOTION_NEUTRAL, NUM_PARTS);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_test::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();

}

//=============================================
//更新
//=============================================
void CEnemy_test::Update()
{
	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

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

		//移動処理
		Move();

		//位置取得
		D3DXVECTOR3 pos = GetPos();

		//過去の位置
		D3DXVECTOR3 oldpos = GetOldPos();

		//移動量取得
		D3DXVECTOR3 move = GetMove();

		//移動量を更新(減速）
		move *= 1.0f - DAMPING_COEFFICIENT;

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

		//マウスの情報取得
		CInputMouse* pMouse = CManager::GetMouse();
		CInputPad* pPad = CManager::GetPad();

		//どっち向いてるか取得
		bool bWay = GetWay();

		Motion(NUM_PARTS); //モーション処理
	}
}

//=============================================
//描画
//=============================================
void CEnemy_test::Draw()
{
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw(NUM_PARTS);
}

//=============================================
//生成
//=============================================
CEnemy_test* CEnemy_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	CEnemy_test* pPlayer = new CEnemy_test;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	pPlayer->Init(); //初期化処理

	pPlayer->SetType(OBJECT_TYPE_NONE); //タイプ設定

	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CEnemy_test::Damage(int nDamage)
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
void CEnemy_test::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CEnemy_test::Move()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	//どっち向いてるか代入
	SetWay(bWay);

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//着地してるか取得
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
		SetMotion(MOTION_NEUTRAL, NUM_PARTS); //現在のモーションを設定
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.y = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
		SetMotion(MOTION_MOVE, NUM_PARTS); //現在のモーションを設定
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //空中
			m_nJumpCnt++; //ジャンプ数加算
			SetMotion(MOTION_ATTACK, NUM_PARTS); //現在のモーションを設定

		}
	}

	//移動量代入
	SetMove(move);

	//着地してるか代入
	SetLanding(bLanding);

}