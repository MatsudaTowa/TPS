//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "player_test.h"
#include "enemy_test.h"

const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//�v���C���[
CPlayer*CGame::m_pPlayer = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�G�f�B�b�g���ĂȂ���ԂɕύX
	//�ǂݍ��ރu���b�N�̏�񏉊���
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//�f�X�g���N�^
//=============================================
CGame::~CGame()
{
}

//=============================================
//������
//=============================================
HRESULT CGame::Init()
{
	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	//�u���b�N����
	LoadBlock(&CGame::BLOCK_FILE);

	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�v���C���[����
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//�v���C���[����
	CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
	CEnemy_test* pEnemy_test = CEnemy_test::Create(D3DXVECTOR3(-850.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	m_GameState = GAME_STATE_NORMAL;
	
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}
	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
	}

}

//=============================================
//�`��
//=============================================
void CGame::Draw()
{
}

//=============================================
//�v���C���[�擾
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumBlock; //�u���b�N�̐�

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}
	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//�G�l�~�[����
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
