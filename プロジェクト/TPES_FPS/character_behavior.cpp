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
void CDush::Move(float fSpeed, D3DXVECTOR3 vecDirection, float fRotMoveY, CCharacter* character, int motion)
{
	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(fRotMoveY) * fSpeed;
		move.z += cosf(fRotMoveY) * fSpeed;
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
