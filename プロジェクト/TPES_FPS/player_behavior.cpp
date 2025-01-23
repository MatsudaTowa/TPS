//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CPlayerMove::CPlayerMove()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerMove::~CPlayerMove()
{
}

//=============================================
//移動処理(プレイヤー)
//=============================================
void CPlayerMove::Move(CCharacter* character)
{

}

//=============================================
//コンストラクタ
//=============================================
CPlayerSliding::CPlayerSliding()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerSliding::~CPlayerSliding()
{
}

//=============================================
//スライディング
//=============================================
void CPlayerSliding::Sliding(CPlayer_test* player)
{
	//スピードがあれば減速
	//if (move.x > 0.0f)
	//{
	//	move.x -= 0.001f;
	//}
	//else if (move.x < 0.0f)
	//{
	//	move.x += 0.001f;
	//}
	//if (move.z > 0.0f)
	//{
	//	move.z -= 0.001f;
	//}
	//else if (move.z < 0.0f)
	//{
	//	move.z += 0.001f;
	//}
	//player->SetMove(move);
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
void CPlayerAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	character->SetMove(character->GetMove() * 0.75f);

	CPlayer_test::Motion_Type Motion;
	Motion = CPlayer_test::Motion_Type::MOTION_ATTACK;
	//モーション代入
	character->SetMotion(Motion);

	if (pMouse->GetPress(0))
	{//射撃ボタンが押されたら
		if (character->m_pGunAttack != nullptr)
		{
			if (character->m_pGun->GetAmmo() > 0)
			{
				++character->m_pGun->m_nRateCnt;

				ShotBullet(character, pCamera, Allegiance, type);
			}
			else
			{
				character->m_pGun->m_pReload->Reload(character->m_pGun);
			}
		}
	}
	if (pMouse->GetRelease(0))
	{
		character->m_pGun->m_nRateCnt = CAssultRifle::DEFAULT_AR_FIRE_RATE;
	}
}

//=============================================
//弾発射
//=============================================
void CPlayerAttack::ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type)
{
	if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
	{
		character->m_pGun->m_nRateCnt = 0;
		//銃から発射 TODO:銃口と方向がおかしい

		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI) * 45.0f,
			character->m_apModel[14]->GetMtxWorld()._42 + 5.0f, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI) * 45.0f);

		//移動量設定
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed(),
			sinf(pCamera->GetRot().x + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
			cosf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed());
		//弾発射
		character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->GetDamage(), Allegiance, type, character->m_pGun);

		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	}
}
