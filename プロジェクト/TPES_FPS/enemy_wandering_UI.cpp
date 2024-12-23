//=============================================
//
//�G�̍�����UI[enemy_wandering_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_wandering_UI.h"
#include "manager.h"

const std::string CEnemy_Wandering_UI::TEXTURE_NAME = "data\\TEXTURE\\wandering_UI.png";

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_Wandering_UI::CEnemy_Wandering_UI(int nPriority):CEnemy_Reaction_UI(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_Wandering_UI::~CEnemy_Wandering_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy_Wandering_UI::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//�e�N�X�`���ǂݍ���
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CEnemy_Reaction_UI::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_Wandering_UI::Uninit()
{
	CEnemy_Reaction_UI::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy_Wandering_UI::Update()
{
	CEnemy_Reaction_UI::Update();
}

//=============================================
//�`��
//=============================================
void CEnemy_Wandering_UI::Draw()
{
	CEnemy_Reaction_UI::Draw();
}
