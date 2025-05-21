//=============================================
//
//�G�̍�����UI[enemy_stan_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_stan_UI.h"
#include "manager.h"

const std::string CEnemy_Stan_UI::TEXTURE_NAME = "data\\TEXTURE\\stan_UI.png";

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_Stan_UI::CEnemy_Stan_UI(int nPriority) :CEnemy_Reaction_UI(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_Stan_UI::~CEnemy_Stan_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy_Stan_UI::Init()
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
void CEnemy_Stan_UI::Uninit()
{
	CEnemy_Reaction_UI::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy_Stan_UI::Update()
{
	CEnemy_Reaction_UI::Update();
}

//=============================================
//�`��
//=============================================
void CEnemy_Stan_UI::Draw()
{
	CEnemy_Reaction_UI::Draw();
}
