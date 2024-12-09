//=============================================
//
//�G�̃����[�h����UI[enemy_reload_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_reload_UI.h"
#include "manager.h"

const std::string CEnemy_Reload_UI::TEXTURE_NAME = "data\\TEXTURE\\magazine.png";
//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_Reload_UI::CEnemy_Reload_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_Reload_UI::~CEnemy_Reload_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy_Reload_UI::Init()
{
	CBillboard::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_Reload_UI::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy_Reload_UI::Update()
{
	CBillboard::Update();
}

//=============================================
//�`��
//=============================================
void CEnemy_Reload_UI::Draw()
{
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CEnemy_Reload_UI* CEnemy_Reload_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy_Reload_UI* pEnemyReloadUI = new CEnemy_Reload_UI;
	if(pEnemyReloadUI == nullptr) { return nullptr;}

	pEnemyReloadUI->SetPos(pos);
	pEnemyReloadUI->SetSize(size);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pEnemyReloadUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pEnemyReloadUI->Init();
	return pEnemyReloadUI;
}
