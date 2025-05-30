//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_state.h"
#include "manager.h"
#include "camera_state.h"
#include "active_player.h"

//=============================================
//�f�t�H���g��Ԃ̏���
//=============================================
void CPlayerState::Default(CActivePlayer* player)
{
}

//=============================================
//�E���g��Ԃ̏���
//=============================================
void CPlayerState::Ult(CActivePlayer* player)
{
}

//=============================================
//�����Ԃ̏���
//=============================================
void CPlayerState::Avoidance(CActivePlayer* player)
{
}

//=============================================
//�ӂ��Ƃя�Ԃ̏���
//=============================================
void CPlayerState::Blown(CActivePlayer* player)
{
}

//=============================================
//�f�t�H���g��Ԃ̏���
//=============================================
void CDefaultState::Default(CActivePlayer* player)
{
	if (player->GetUlt() != nullptr)
	{
		player->GetUlt()->Update();
	}

	player->Input();
}

//=============================================
//�E���g��Ԃ̏���
//=============================================
void CUltState::Ult(CActivePlayer* player)
{
	bool isFinish = false;
	if (player->GetUlt() != nullptr)
	{
		isFinish = player->GetUlt()->Action(player);
	}

	if (isFinish)
	{
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->ChangeCameraState(new CThirdView);
		player->ChangePlayerState(new CDefaultState);
	}
}

//=============================================
//�L�����N�^�[�̉�����
//=============================================
void CAvoidanceState::Avoidance(CActivePlayer* player)
{

}

//=============================================
//�R���X�g���N�^
//=============================================
CBlownState::CBlownState():m_nStanCnt(INT_ZERO)
{
}

//=============================================
//�L�����N�^�[�̐�����΂�����
//=============================================
void CBlownState::Blown(CActivePlayer* player)
{
	if (player->GetLaunding())
	{//���n������
		++m_nStanCnt;
		player->SetMotion(CPlayer::MOTION_STAN);
		//�X�^�b�N���Ȃ��悤�ɓ����蔻�薳��
		player->SetEnemyColision(true);
		if (m_nStanCnt > player->GetStanFrame())
		{//�X�^�����I�������
			//�����蔻�蕜��
			player->SetEnemyColision(false);
			m_nStanCnt = INT_ZERO;
			player->ChangePlayerState(new CDefaultState);
		}
	}
}
