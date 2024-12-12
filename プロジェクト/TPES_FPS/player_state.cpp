//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_state.h"

//=============================================
//�f�t�H���g��Ԃ̏���
//=============================================
void CPlayerState::Default(CPlayer_test* player)
{
}

//=============================================
//�E���g��Ԃ̏���
//=============================================
void CPlayerState::Ult(CPlayer_test* player)
{
}

//=============================================
//�f�t�H���g��Ԃ̏���
//=============================================
void CDefaultState::Default(CPlayer_test* player)
{
	if (player->m_pUlt != nullptr)
	{
		player->m_pUlt->Update();
	}

	if (player->GetFinish())
	{
		//���͏���
		player->Input();
	}

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		player->m_pSliding->Sliding(player);
	}
	else
	{
		player->m_pCharacterState->Move(player);
	}
}

//=============================================
//�E���g��Ԃ̏���
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
		player->ChangePlayerState(new CDefaultState);
	}
}
