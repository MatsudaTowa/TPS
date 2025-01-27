//=============================================
//
//プレイヤーのステートパターン[player_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_state.h"
#include "manager.h"
#include "camera_state.h"

//=============================================
//デフォルト状態の処理
//=============================================
void CPlayerState::Default(CPlayer* player)
{
}

//=============================================
//ウルト状態の処理
//=============================================
void CPlayerState::Ult(CPlayer* player)
{
}

//=============================================
//回避状態の処理
//=============================================
void CPlayerState::Avoidance(CPlayer* player)
{
}

//=============================================
//デフォルト状態の処理
//=============================================
void CDefaultState::Default(CPlayer* player)
{
	if (player->m_pUlt != nullptr)
	{
		player->m_pUlt->Update();
	}

	if (player->GetFinish())
	{

	}

	{
		player->m_pCharacterState->Move(player);
	}
}

//=============================================
//ウルト状態の処理
//=============================================
void CUltState::Ult(CPlayer* player)
{
	bool isFinish = false;
	if (player->m_pUlt != nullptr)
	{
		isFinish = player->m_pUlt->Action(player);
	}

	if (isFinish)
	{
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->ChangeCameraState(new CThirdView);
		player->ChangePlayerState(new CDefaultState);
	}
}

//=============================================
//キャラクターの回避状態
//=============================================
void CAvoidanceState::Avoidance(CPlayer* player)
{

}
