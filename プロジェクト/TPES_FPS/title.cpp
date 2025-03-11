//=============================================
//
//�^�C�g������[title.cpp]
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

//�X�|�[���ʒu
const D3DXVECTOR3 CTitle::PLAYER_SPAWN = { 0.0f, 0.5f, -300.0f }; 

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

	//�v���C���[����
	CPlayer::Create();

	//�^�C�g��UI����
    m_pTitleScreen[0] = CTitle_Screen::Create(LOGO_POS, LOGO_SIZE,CTitle_Screen::TITLE_UI::UI_TITLE_ROGO);

    m_pTitleScreen[1]=CTitle_Screen::Create(UI_POS, UI_SIZE, CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON);

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle::Uninit()
{
	//�T�E���h���~�߂�
	CManager::GetInstance()->GetSound()->StopSound();

	//�I�u�W�F�N�g��j��
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTitle::Update()
{
	//�C���v�b�g�擾
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();
    CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A) || pMouse->GetTrigger(0))
    {
		//�`���[�g���A���ɑJ��
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
    }
}

//=============================================
//�`��
//=============================================
void CTitle::Draw()
{
}