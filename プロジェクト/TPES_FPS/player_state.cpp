//=============================================
//
//�v���C���[�̃X�e�[�g�p�^�[��[player_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_state.h"
#include "manager.h"
#include "camera_state.h"

//=============================================
//�f�t�H���g��Ԃ̏���
//=============================================
void CPlayerState::Default(CPlayer* player)
{
}

//=============================================
//�E���g��Ԃ̏���
//=============================================
void CPlayerState::Ult(CPlayer* player)
{
}

//=============================================
//�����Ԃ̏���
//=============================================
void CPlayerState::Avoidance(CPlayer* player)
{
}

//=============================================
//�ӂ��Ƃя�Ԃ̏���
//=============================================
void CPlayerState::Blown(CPlayer* player)
{
}

//=============================================
//�f�t�H���g��Ԃ̏���
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
		player->Input();
	}
}

//=============================================
//�E���g��Ԃ̏���
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
//�L�����N�^�[�̉�����
//=============================================
void CAvoidanceState::Avoidance(CPlayer* player)
{

}

//=============================================
//�R���X�g���N�^
//=============================================
CBlownState::CBlownState():m_nStanCnt(0)
{
}

//=============================================
//�L�����N�^�[�̐�����΂�����
//=============================================
void CBlownState::Blown(CPlayer* player)
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
			m_nStanCnt = 0;
			player->ChangePlayerState(new CDefaultState);
		}
	}
}
