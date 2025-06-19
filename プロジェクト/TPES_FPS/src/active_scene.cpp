//=============================================
//
//�V�ׂ�V�[��[active_scene.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_scene.h"

//=============================================
// �R���X�g���N�^
//=============================================
CActiveScene::CActiveScene():m_pState(nullptr)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CActiveScene::~CActiveScene()
{
}

//=============================================
// ������
//=============================================
HRESULT CActiveScene::Init()
{
	if (m_pState == nullptr)
	{
		m_pState = new CNormal;
	}
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CActiveScene::Uninit()
{
}

//=============================================
// �X�V
//=============================================
void CActiveScene::Update()
{
	if (m_nPauseCnt <= PAUSE_POSSIBLE_FLAME)
	{
		++m_nPauseCnt;
	}
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Pause(this);
	}
}

//=============================================
// �`��
//=============================================
void CActiveScene::Draw()
{
}

//=============================================
// �X�V���~�߂邩
//=============================================
void CActiveScene::UpdateObjectDecision(bool isActive)
{
	for (int i = 0; i < CObject::PRI_MAX; ++i)
	{
		for (int j = 0; j < CObject::MAX_OBJECT; ++j)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(i, j);	//�擪�擾

			if (pObj == nullptr)
			{
				continue;
			}

			if (pObj->GetisActive() != isActive)
			{
				pObj->SetisActive(isActive);
			}
		}
	}
}

//=============================================
// �X�V���~�߂邩
//=============================================
void CActiveScene::LoadBlock(const std::string& pFileName)
{
	//�t�@�C���̓ǂݍ���
	std::ifstream File(pFileName, std::ios::binary);

	//�t�@�C�����J���Ȃ�������֐��𔲂���
	if (!File.is_open())
	{
		return;
	}

	//��������u���b�N���ǂݍ��ݗp
	int NumBlock = 0;

	File.read(reinterpret_cast<char*>(&NumBlock), sizeof(int));

	if (NumBlock > 0)
	{
		//��������u���b�N�̏������ϐ�
		std::vector<LOAD_BLOCK> info(NumBlock);

		//�t�@�C������ǂݍ��񂾃f�[�^���i�[
		File.read(reinterpret_cast<char*>(info.data()), sizeof(LOAD_BLOCK) * NumBlock);

		//�C�e���[�^�ŉ񂵂Đ���
		for (auto& itr : info)
		{
			CBlock::Create(itr.type, itr.pos, itr.rot);
		}
	}

	File.close();
}

//=============================================
// �X�e�[�g���
//=============================================
void CActiveScene::ChangeState(CActiveSceneState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
}
