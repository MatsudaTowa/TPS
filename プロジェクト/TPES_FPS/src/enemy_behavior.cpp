//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "enemy_behavior.h"
#include "manager.h"
#include "player.h"
#include "object.h"
#include "normal_enemy.h"

//=============================================
//コンストラクタ
//=============================================
CEnemyMove::CEnemyMove():m_move_vec(VEC3_RESET_ZERO)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyMove::~CEnemyMove()
{
}

//=============================================
//移動処理(エネミー)
//=============================================
void CEnemyMove::Move(CCharacter* character)
{
	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(m_move_vec);

	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	CEnemy::Motion_Type Motion;

	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // 動いてない。
		Motion = CEnemy::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CEnemy::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // 動いてない。
		move.x = FLOAT_ZERO;
		move.z = FLOAT_ZERO;
	}
	else
	{
		move.x += sinf(rotMoveY) * character->GetSpeed();
		move.z += cosf(rotMoveY) * character->GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	character->SetRot(rot);
	//移動量代入
	character->SetMove(move);
	//モーション代入
	character->SetMotion(Motion);
}

//=============================================
//コンストラクタ
//=============================================
CEnemyGunAttack::CEnemyGunAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyGunAttack::~CEnemyGunAttack()
{
}

//=============================================
//攻撃処理(エネミー)
//=============================================
void CEnemyGunAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	CNormalEnemy::Motion_Type Motion;
	Motion = CNormalEnemy::Motion_Type::MOTION_ATTACK;
	//モーション代入
	character->SetMotion(Motion);

	CGun* gun = character->GetGun();

	D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI),
		character->m_apModel[14]->GetMtxWorld()._42 + CORRECTION_Y, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI));

	D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(character->GetRot().y + D3DX_PI) * gun->GetBulletSpeed(),
		0.0f, cosf(character->GetRot().y + D3DX_PI) * gun->GetBulletSpeed());

	if (gun->GetAmmo() > INT_ZERO)
	{
		int nRateCnt = gun->GetRateCnt();

		++nRateCnt;
		if (nRateCnt >= gun->GetFireRate())
		{
			nRateCnt = INT_ZERO;
			//弾発射
			gun->m_pShot->Shot(ShotPos, ShotMove, gun->GetSize(), gun->GetDamage(), Allegiance, gun);
		}

		gun->SetRateCnt(nRateCnt);
	}
	else
	{
		gun->m_pReload->Reload(gun);
	}

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), FLOAT_ZERO, cosf(character->GetRot().y + D3DX_PI) };

	// レイキャストを実行し、障害物があるか判定TODO:いったんブロックは除外
	if (character->PerformRaycast_Smoke(vec, character).hit)
	{
		character->ChangeState(new CConfusionState);
	}
}

//=============================================
//プレイヤーのほうを向かせる
//=============================================
void CEnemyGunAttack::LookAtPlayer(CCharacter* character)
{
	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
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

		//プレイヤーとの距離算出
		D3DXVECTOR3 Distance = pPlayer->GetPos() - character->GetPos();

		//プレイヤーに向ける角度を算出
		float fAngle = atan2f(Distance.x,Distance.z);

		//親クラスからrotを取得
		D3DXVECTOR3 rot = character->GetRot();

		rot.y = fAngle + D3DX_PI;

		character->SetRot(rot);
	}
}

//サイズ
const D3DXVECTOR3 CEnemyConfusion::SIZE = { 20.0f,20.0f,0.0f };

//=============================================
//コンストラクタ
//=============================================
CEnemyConfusion::CEnemyConfusion() : m_isRight(false), m_TurnCnt(INT_ZERO), m_pReaction()
{	
}

//=============================================
//デストラクタ
//=============================================
CEnemyConfusion::~CEnemyConfusion()
{
	if (m_pReaction != nullptr)
	{
		m_pReaction->Uninit();
		m_pReaction = nullptr;
	}
}

//=============================================
//混乱
//=============================================
void CEnemyConfusion::Confusion(CCharacter* character, float StartRot_y)
{
	if (m_pReaction == nullptr)
	{
		m_pReaction = CEnemy_Reaction_UI::Create({ character->m_apModel[1]->GetMtxWorld()._41,
			character->m_apModel[1]->GetMtxWorld()._42 + CORRECTION_VALUE,
			character->m_apModel[1]->GetMtxWorld()._43 }, SIZE,  CEnemy_Reaction_UI::REACTION::REACTION_CONFUSION);
	}
	//現在の方向を取得
	D3DXVECTOR3 rot = character->GetRot();

	//移動量を算出
	float Rot_Answer_y = rot.y - StartRot_y;

	//方向移動処理
	MoveRot(rot, Rot_Answer_y, character);

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), FLOAT_ZERO, cosf(character->GetRot().y + D3DX_PI) };

	D3DXVec3Normalize(&vec, &vec);

	CCharacter::RayHitInfo HitPlayerInfo;

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);
	
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if (HitPlayerInfo.hit && HitPlayerInfo.distance < HitBlockInfo.distance)
	{//見つけたら
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		character->ChangeState(new CShotState);
		return;
	}
	if (character->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		character->ChangeState(new CStanState);
		return;
	}
	if (m_TurnCnt >= NUM_TURN)
	{//上限に達したら
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		m_TurnCnt = INT_ZERO;
		character->ChangeState(new CMoveState);
		return;
	}
}

//=============================================
//方向移動
//=============================================
void CEnemyConfusion::MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character)
{
	if (m_isRight)
	{
		rot.y += ROT_MOVE;

		if (Rot_Answer_y > LOOK_RANGE)
		{//範囲に到達したら逆回転
			m_isRight = false;
			++m_TurnCnt;
		}
	}
	if (!m_isRight)
	{
		rot.y -= ROT_MOVE;

		if (Rot_Answer_y < -LOOK_RANGE)
		{//範囲に到達したら逆回転
			m_isRight = true;
			++m_TurnCnt;
		}
	}
	character->SetRot(rot);
}

//=============================================
//コンストラクタ
//=============================================
CEnemyStan::CEnemyStan()
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyStan::~CEnemyStan()
{
}

//=============================================
//スタン処理
//=============================================
void CEnemyStan::Stan(CCharacter* character)
{
	character->SetMotion(CNormalEnemy::Motion_Type::MOTION_STAN);
}
