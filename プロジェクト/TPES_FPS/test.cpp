//=============================================
//
//�e�X�g�V�[��[test.cpp]
//Author Matsuda Towa
//
//=============================================
#include "test.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//�ǂݍ��ރu���b�N���̃t�@�C��
const std::string CTest::BLOCK_FILE = "data\\FILE\\block_data_tutorial.bin";

//=============================================
// �R���X�g���N�^
//=============================================
CTest::CTest()
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CTest::~CTest()
{
}

//=============================================
// ������
//=============================================
HRESULT CTest::Init()
{
	//�u���b�N����
	LoadBlock(CTest::BLOCK_FILE);

	CField::Create(VEC3_RESET_ZERO, { 1000.0f,0.0f,1000.0f });

	//�v���C���[����
	CPlayer::Create();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CTest::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
// �X�V
//=============================================
void CTest::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	//if (m_bEdit == false)
	//{

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
// �`��
//=============================================
void CTest::Draw()
{
}

//=============================================
// �u���b�N�ǂݍ���
//=============================================
void CTest::LoadBlock(const std::string& pFileName)
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
