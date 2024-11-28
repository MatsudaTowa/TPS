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

//プレイヤーをリスポーンされる座標
const float CPlayer_test::DEADZONE_Y = -100.0f;

CAmmo_UI* CPlayer_test::m_pAmmoUI = nullptr;
CLife_UI* CPlayer_test::m_pLifeUI = nullptr;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority),m_Raticle()
{//イニシャライザーでメンバ変数初期化
	if (m_pMove == nullptr)
	{
		m_pMove = new CPlayerMove;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CPlayerAttack;
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

	//現在のシーンを取得 TODO:シーン参照するな
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//残弾数初期化
		if (m_pAmmoUI == nullptr)
		{
			m_pAmmoUI = new CAmmo_UI;

			m_pAmmoUI->Init();
		}
		//体力UI初期化
		if (m_pLifeUI == nullptr)
		{
			m_pLifeUI = new CLife_UI;

			m_pLifeUI->Init();
		}
	}

	m_Raticle = nullptr;

	m_bRelorad = false;

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetInstance()->GetModel();
	}

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//ムーブ値代入
	SetMove(move);

	//パーツ読み込み
	Load_Parts("data\\motion_soldier.txt");

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
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
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

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}
	CCharacter::Update();
	ColisionEnemy();


	if (m_bRelorad == true)
	{//リロード中だったら
		m_bRelorad = m_pGun->Reload(); //リロードし終わったらfalseが返ってくる
	}

	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetAmmo_UI(m_pGun->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
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
			m_pCharacterState->Move(this);
		}

		//カメラ情報取得
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		}

		//どっち向いてるか取得
		bool bWay = GetWay();

		Motion(NUM_PARTS); //モーション処理
	}

	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//描画
//=============================================
void CPlayer_test::Draw()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse() ;
	pMouse->Debug();
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();
	//プレイヤーのデバッグ表示
	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

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
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
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
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pMouse->GetPress(1))
	{//マウスが押されてる間は
		//射撃状態に変更
		ChangeState(new CShotState);

		//モーションを変更 TODO:覗きこむモーションに
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //レティクルのほうを向きたいので

		if (m_Raticle == nullptr)
		{//使われていなかったら
			m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		}
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, this);
	}

	if (pMouse->GetRelease(1))
	{//マウスが離されたら
		//移動状態に変更
		ChangeState(new CMoveState);

		if(m_Raticle != nullptr)
		{//使われていたら
			m_Raticle->Uninit();
			m_Raticle = nullptr;
		}
	}

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

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
//プレイヤーの方向をカメラのほうへ
//=============================================
void CPlayer_test::ResetRot()
{
	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y;

	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot);
}

//=============================================
//エネミーとの当たり判定
//=============================================
void CPlayer_test::ColisionEnemy()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//オブジェクトに要素が入っていたら
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//ブロックとの当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					//安全にダウンキャスト
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

					CheckColisionEnemy(pEnemy, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
	
}

void CPlayer_test::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nEnemyPartsCnt = 0; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
	{
		D3DXVECTOR3 Enemypos = { pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._41,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._42,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 EnemyMinpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMin();
		D3DXVECTOR3 EnemyMaxpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			Enemypos, EnemyMinpos, EnemyMaxpos);

		if (colision == CColision::COLISION::COLISON_X)
		{
			// X軸衝突時の処理
			SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_Z)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
		}
	}
}

//======================================================
//絶対値でどちらの方向に大きく移動した計算
//======================================================
void CPlayer_test::CheckVec(D3DXVECTOR3& movementVec)
{
	if (fabs(movementVec.x) > fabs(movementVec.y) && fabs(movementVec.x) > fabs(movementVec.z))
	{
		// X軸衝突時の処理
		SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
	}
	else if (fabs(movementVec.y) > fabs(movementVec.x) && fabs(movementVec.y) > fabs(movementVec.z))
	{
		// Y軸衝突時の処理
		SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
	}
	else
	{
		// Z軸衝突時の処理
		SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer_test::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n弾数:%d\n体力:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(),GetLife());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
