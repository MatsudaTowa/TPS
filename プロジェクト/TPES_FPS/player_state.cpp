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
void CPlayerState::Default(CPlayer_test* player)
{
}

//=============================================
//ウルト状態の処理
//=============================================
void CPlayerState::Ult(CPlayer_test* player)
{
}

//=============================================
//デフォルト状態の処理
//=============================================
void CDefaultState::Default(CPlayer_test* player)
{
	if (player->m_pUlt != nullptr)
	{
		player->m_pUlt->Update();
	}

	if (player->GetFinish())
	{
		//入力処理
		player->Input();
	}

	{
		player->m_pCharacterState->Move(player);
	}
}

//=============================================
//ウルト状態の処理
//=============================================
void CUltState::Ult(CPlayer_test* player)
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
