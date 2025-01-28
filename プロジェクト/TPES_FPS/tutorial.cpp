//=============================================
//
//3DTemplate[tutorial.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial.h"
#include "tutorial_screen.h"
#include "player.h"

const std::string CTutorial::ENEMY_FILE = "data\\FILE\\enemy_001.txt";
const std::string CTutorial::BLOCK_FILE = "data\\FILE\\block_data_tutorial.bin";
const std::string CTutorial::WALL_FILE = "data\\FILE\\wall_002.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CTutorial::CTutorial():m_pTutorial_UI()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTutorial::~CTutorial()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorial::Init()
{
	CScene::Init();

	CPlayer* pplayer = CPlayer::Create(CPlayer::PLAYER_SPAWN_POS, CPlayer::PLAYER_SPAWN_ROT, CPlayer::PLAYER_LIFE);

	LoadBlock(&BLOCK_FILE);
	LoadEnemy(&ENEMY_FILE);
	LoadWall(&WALL_FILE);
	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 1000.0f));

	CTutorial_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f), D3DXVECTOR2(200.0f, 100.0f), CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT);

	if (m_pTutorial_UI == nullptr)
	{
		m_pTutorial_UI = new CTutorial_UI;
		m_pTutorial_UI->Init();
	}

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorial::Uninit()
{
	if (m_pTutorial_UI != nullptr)
	{
		m_pTutorial_UI->Uninit();
		m_pTutorial_UI = nullptr;
	}
	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTutorial::Update()
{
	if (m_pTutorial_UI != nullptr)
	{
		m_pTutorial_UI->Update();
	}

	if (CEnemy::m_NumEnemy <= 0)
	{//�G�����Ȃ��Ȃ�����ăX�|�[��
		LoadEnemy(&ENEMY_FILE);
	}

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetPad();
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_GAME);
	}
}

//=============================================
//�`��
//=============================================
void CTutorial::Draw()
{
}

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CTutorial::LoadBlock(const std::string* pFileName)
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

//=============================================
//�Ǔǂݍ���
//=============================================
void CTutorial::LoadWall(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumWall; //�ǂ̐�

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

		if (!strcmp(aDataSearch, "NUM_WALL"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumWall);
		}
		if (!strcmp(aDataSearch, "WALLSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_WALLSET"))
				{
					//�u���b�N����
					CWall::Create(m_LoadWall.pos, m_LoadWall.rot, m_LoadWall.size);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.pos.x,
						&m_LoadWall.pos.y,
						&m_LoadWall.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.rot.x,
						&m_LoadWall.rot.y,
						&m_LoadWall.rot.z);
				}
				else if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.size.x,
						&m_LoadWall.size.y,
						&m_LoadWall.size.z);
				}
			}
		}
	}
}

//=============================================
//�G�ǂݍ���
//=============================================
void CTutorial::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumEnemy; //�G�l�~�[�̐�

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

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//�G�l�~�[����
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}
