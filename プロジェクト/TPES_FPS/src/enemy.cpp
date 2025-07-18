//=============================================
//
//敵の処理[enemy.cpp]
//Author Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "wave.h"
#include "player.h"
#include "normal_enemy.h"
#include "boss_enemy.h"

//エネミー総数
int CEnemy::m_NumEnemy = 0;

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority),
m_Type(),				//敵のタイプ
m_isStencil(false),		//型抜きするか
m_StencilCnt(INT_ZERO)	//型抜きする時間
{//イニシャライザーでメンバ変数初期化
	//総数追加
	m_NumEnemy++;
}

//=============================================
//デストラクタ
//=============================================
CEnemy::~CEnemy()
{
	//総数減少
	m_NumEnemy--;
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//ステート変更フレーム代入
	SetStateFrame(DAMAGE_FRAME);

	//スタンフレーム数代入
	SetStanFrame(STAN_FRAME);

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(VEC3_RESET_ZERO);

	//ムーブ値代入
	SetMove(move);

	m_Motion = CEnemy::Motion_Type::MOTION_MAX; //ニュートラルに設定

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy::Update()
{
	CCharacter::Update();

	if (m_pCharacterState != nullptr)
	{
		m_pCharacterState->Move(this);

		m_pCharacterState->Stan(this);

		m_pCharacterState->Confusion(this);

		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_ENEMY, this);
	}

	if (m_isStencil)
	{//ステンシルテストが有効だったら
		++m_StencilCnt;
		if (m_StencilCnt > STENCIL_FLAME)
		{//フレームに到達していたら
			m_StencilCnt = INT_ZERO;
			//ステンシルテストを無効に
			m_isStencil = false;
		}
	}

	//ダメージステートの切り替えTODO:これもステートパターンで
	ChangeDamageState();

	if (GetPos().y < DEADZONE_Y)
	{//リスポーン処理
		ReSpawn();
	}
}

//=============================================
//描画
//=============================================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ

	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, m_isStencil);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();	
	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================
//生成
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE::ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
		pEnemy->Load_Parts("data\\motion_enemy000.bin");
		break;
	case ENEMY_TYPE::ENEMY_TYPE_BOSS:
		pEnemy = new CBossEnemy;
		pEnemy->Load_Parts("data\\motion_boss.bin");
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type;
	pEnemy->SetPos(pos); //pos設定
	pEnemy->SetRot(rot); //rot設定

	pEnemy->Init(); //初期化処理

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //タイプ設定

	return pEnemy;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CEnemy::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();
	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > INT_ZERO)
	{//ダメージ状態以外でHPが残ってたら
		nLife -= nDamage;

		if (!m_isStencil)
		{
			m_isStencil = true;
		}

		if (state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//ダメージ状態に変更
			state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

			//状態代入
			SetState(state);
		}

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= INT_ZERO)
	{//HPが0以下だったら
		//現在のシーンを取得
		CScene::MODE pScene = CScene::GetSceneMode();

		if (pScene == CScene::MODE_GAME)
		{
			CScore* pScore = CWave::GetScore();

			int nAddScore = INT_ZERO;

			switch (m_Type)
			{
			case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
				nAddScore = DEFAULT_SCORE;
				break;
			case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
				nAddScore = BOSS_SCORE;
				break;
			default:
				assert(false);
				break;
			}
			pScore->AddScore(nAddScore);
		}
		
		//終了
		Uninit();
	}
}

//=============================================
//ウルトが当たったとこの処理
//=============================================
void CEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	//ウルトの着地地点と敵の方向情報
	D3DXVECTOR3 Vector = UltPos - GetPos();

	//対象物との角度計算
	float angle = atan2f(Vector.x, Vector.z);

	D3DXVECTOR3 move = GetMove();
	
	if (GetLaunding())
	{
		//反対方向に吹っ飛ばすのでスピードはマイナス
		move.x += sinf(angle) * (-GetSpeed() * ULT_KNOCKBACK_SPEED);
		move.y += ULT_KNOCKBACK_Y;
		move.z += cosf(angle) * (-GetSpeed() * ULT_KNOCKBACK_SPEED);
	}

	//移動量代入
	SetMove(move);

	Damage(nDamage);

}

//=============================================
//プレイヤーとレイが当たっているか
//=============================================
CCharacter::RayHitInfo CEnemy::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info = {};

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		//プレイヤーを探す
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//レイを原点からの差分から飛ばす(yはエネミーから飛ばす際の高さ調整)
		D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y,character->GetPos().z - pPlayer->GetPos().z };
		for (int nParts = 0; nParts < pPlayer->GetNumParts(); nParts++)
		{
			//レイを飛ばしプレイヤーと当たるかチェック
			D3DXIntersect(pPlayer->m_apModel[nParts]->GetModelInfo(nParts).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
			if (Info.hit)
			{
				return Info;
			}
		}
	}
	return Info;
}

//=============================================
//リスポーン
//=============================================
void CEnemy::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 EnemyPos = GetPos();

	EnemyPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(EnemyPos);
}