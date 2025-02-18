//=============================================
//
//3DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "title.h"
#include "title_screen.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include"player.h"
#include "field.h"
#include "manager.h"
#include "sound.h"

//�u���b�N�̃t�@�C���p�X
const std::string CTitle::BLOCK_FILE = "data\\FILE\\block.txt";

//���̃T�C�Y
const D3DXVECTOR3 CTitle::LOGO_POS = { SCREEN_WIDTH * HALF,200.0f,0.0f };

//���̃T�C�Y
const D3DXVECTOR3 CTitle::UI_POS = { SCREEN_WIDTH * HALF, 600.0f, 0.0f };

//���̃T�C�Y
const D3DXVECTOR3 CTitle::FIELD_SIZE = { 1000.0f,0.0f,1000.0f };

//���S�̃T�C�Y
const D3DXVECTOR2 CTitle::LOGO_SIZE = { 400.0f,200.0f };

//UI�̃T�C�Y
const D3DXVECTOR2 CTitle::UI_SIZE = { 200.0f, 50.0f };

const D3DXVECTOR3 CTitle::PLAYER_SPAWN = { 0.0f, 0.5f, -300.0f }; //�X�|�[���ʒu



//=============================================
//�R���X�g���N�^
//=============================================
CTitle::CTitle()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTitle::~CTitle()
{
}

//=============================================
//������
//=============================================
HRESULT CTitle::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
    //�n�ʐ���
    CField::Create(VEC3_RESET_ZERO, FIELD_SIZE);

	//�u���b�N����
	//LoadBlock(&CTitle::BLOCK_FILE);

	//�v���C���[����
	CPlayer::Create();

    m_pTitleScreen[0] = CTitle_Screen::Create(LOGO_POS, LOGO_SIZE,CTitle_Screen::TITLE_UI::UI_TITLE_ROGO);

    m_pTitleScreen[1]=CTitle_Screen::Create(UI_POS, UI_SIZE, CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON);

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTitle::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();
    CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A) || pMouse->GetTrigger(0))
    {
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
    }
}

//=============================================
//�`��
//=============================================
void CTitle::Draw()
{
}

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CTitle::LoadBlock(const std::string* pFileName)
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
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
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