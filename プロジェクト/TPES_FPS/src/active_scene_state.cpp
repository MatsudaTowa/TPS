//=============================================
//
//�A�N�e�B�u�V�[���̃X�e�[�g�p�^�[��[active_scene_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_scene_state.h"
#include "active_scene.h"
#include "manager.h"

//=============================================
// �R���X�g���N�^
//=============================================
CNormal::CNormal()
{
	while (1)
	{
		int nCnt = ShowCursor(FALSE);
		if (nCnt > 0)
		{
			continue;
		}
		break;
	}
	ShowCursor(FALSE);
}

//=============================================
// �ʏ폈��
//=============================================
void CNormal::Normal(CActiveScene* active_scene)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g��������
	active_scene->UpdateObjectDecision(true);
	//�J������
	CManager::GetInstance()->GetCamera()->SetActive(true);
}

//�|�[�YUI�\���ʒu
const D3DXVECTOR3 CPause::POS[CPause::MAX]
{
	{SCREEN_WIDTH * HALF,200.0f,0.0f},
	{SCREEN_WIDTH * HALF,400.0f,0.0f},
	{SCREEN_WIDTH * HALF,600.0f,0.0f}
};

//=============================================
// �R���X�g���N�^
//=============================================
CPause::CPause() :
	m_pSelect(),	//�Z���N�gUI�̐�
	m_pMask(nullptr)	//�����}�X�N
{
	while (1)
	{
		int nCnt = ShowCursor(TRUE);
		if (nCnt < 0)
		{
			continue;
		}
		break;
	}

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			continue;
		}
		switch (i)
		{
		case CONTINUE:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectContinue);
			break;
		case RETRY:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectRetry);
			break;
		case QUIT:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectQuit);
			break;
		default:
			break;
		}

	}

	m_pMask = CMask::Create(new CPauseMask);
}

//=============================================
// �f�X�g���N�^
//=============================================
CPause::~CPause()
{
	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->Uninit();
			m_pSelect[i] = nullptr;
		}
	}
	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
}

//=============================================
// �|�[�Y����
//=============================================
void CPause::Pause(CActiveScene* active_scene)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g���~�߂�
	active_scene->UpdateObjectDecision(false);

	//�|�[�Y�֘A�̃I�u�W�F�N�g�̍X�V�͋���
	m_pMask->SetisActive(true);

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->SetisActive(true);
			m_pSelect[m_nSelect]->SetSelect(false);
		}
	}

	CInputKeyboard* pKeyBoard = CManager::GetInstance()->GetKeyboard();

	if (pKeyBoard->GetTrigger(DIK_S))
	{
		if (m_nSelect >= CPause::QUIT)
		{
			m_nSelect = CPause::CONTINUE;
			return;
		}
		++m_nSelect;
	}
	if (pKeyBoard->GetTrigger(DIK_W))
	{
		if (m_nSelect <= CPause::CONTINUE)
		{
			m_nSelect = CPause::QUIT;
			return;
		}
		--m_nSelect;
	}

	m_pSelect[m_nSelect]->SetSelect(true);

	if (pKeyBoard->GetTrigger(DIK_RETURN))
	{
		active_scene->ResetPauseCnt();
		HandlePoseSelection(active_scene);
		return;
	}

	//�J������
	CManager::GetInstance()->GetCamera()->SetActive(false);

	//���̓f�o�C�X�擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_P) && active_scene->GetPauseKey())
	{
		active_scene->ResetPauseCnt();
		CancelPause(active_scene);
	}
}
