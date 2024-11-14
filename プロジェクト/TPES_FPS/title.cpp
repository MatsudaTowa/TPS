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
#include"player_test.h"
#include "field.h"
#include "manager.h"
#include "sound.h"

const std::string CTitle::BLOCK_FILE = "data\\FILE\\block.txt";


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
    //�n�ʐ���
    CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�u���b�N����
	LoadBlock(&CTitle::BLOCK_FILE);

	//�v���C���[����
	CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(0.0f, 0.5f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);

    m_pTitleScreen[0] = CTitle_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,150.0f,0.0f),D3DXVECTOR2(400.0f,200.0f),CTitle_Screen::TITLE_UI::UI_TITLE_ROGO);

    m_pTitleScreen[1]=CTitle_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), D3DXVECTOR2(200.0f, 100.0f), CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON);

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle::Uninit()
{
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTitle::Update()
{
    CObject::UpdateAll();
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputPad* pPad = CManager::GetPad();

    //CFade*pFade= CFade::GetFade();
    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::m_pFade->SetFade(CScene::MODE::MODE_GAME);
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