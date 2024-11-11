//=============================================
//
//キャラクターのストラテジーパターン[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#include "character_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CMove::CMove()
{
}

//=============================================
//デストラクタ
//=============================================
CMove::~CMove()
{
}

//=============================================
//コンストラクタ
//=============================================
CDush::CDush()
{
}

//=============================================
//デストラクタ
//=============================================
CDush::~CDush()
{
}

//=============================================
//移動処理
//=============================================
void CDush::Move(D3DXVECTOR3 vecDirection, float fRotMoveY, CCharacter* character, int motion)
{
	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(fRotMoveY) * character->GetSpeed();
		move.z += cosf(fRotMoveY) * character->GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = fRotMoveY + D3DX_PI;
	//rotを代入
	character->SetRot(rot);
	//移動量代入
	character->SetMove(move);
	//モーション代入
	character->SetMotion(motion);
}

//=============================================
//コンストラクタ
//=============================================
CAttack::CAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CAttack::~CAttack()
{
}

//=============================================
//コンストラクタ
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//攻撃処理(プレイヤー)
//=============================================
void CPlayerAttack::Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, 
CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character)
{
	pGun->m_nRateCnt++;
	if (pGun->m_nRateCnt >= CAssultRifle::DEFAULT_AR_FIRE_RATE)
	{
		pGun->m_nRateCnt = 0;
		//弾発射
		pGun->ShotBullet(pos,move,size,nDamage,Allegiance,type);
	}
}

//=============================================
//コンストラクタ
//=============================================
CEnemyAttack::CEnemyAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CEnemyAttack::~CEnemyAttack()
{
}

//=============================================
//攻撃処理(エネミー)
//=============================================
void CEnemyAttack::Attack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage,
CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* pGun, CCharacter* character)
{
}

