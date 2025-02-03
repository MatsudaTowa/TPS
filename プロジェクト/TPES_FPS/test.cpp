//=============================================
//
//�e�X�g�V�[��[test.cpp]
//Auther Matsuda Towa
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
	LoadBlock(&CTest::BLOCK_FILE);

	CField::Create({ 0.0f,0.0f,0.0f }, { 1000.0f,0.0f,1000.0f });

	//�v���C���[����
	CPlayer* pplayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
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
void CTest::LoadBlock(const std::string* pFileName)
{
	//��������u���b�N���ǂݍ��ݗp
	int NumBlock = 0;

	//��������u���b�N���ǂݍ��ݗp
	LOAD_BLOCK Info[256];

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "rb");

	if (pFile != NULL)
	{
		//�G�̎g�p���Ă鐔�̓ǂݍ���
		fread(&NumBlock, sizeof(int), 1, pFile);

		//�G�̎g�p�����A�G�̓ǂݍ���
		fread(&Info[0], sizeof(LOAD_BLOCK), NumBlock, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < NumBlock; nCnt++)
	{
		CBlock::Create(Info[nCnt].type, Info[nCnt].pos, Info[nCnt].rot, 1, false);
	}
}
