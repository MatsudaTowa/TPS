//=============================================
//
//�G�̃����[�h����UI[enemy_reload_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_reload_UI.h"
#include "manager.h"

//�e�N�X�`���p�X
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
	//�e�N���X�̏�����
	CBillboard::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_Reload_UI::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy_Reload_UI::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();
}

//=============================================
//�`��
//=============================================
void CEnemy_Reload_UI::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CEnemy_Reload_UI* CEnemy_Reload_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy_Reload_UI* pEnemyReloadUI = new CEnemy_Reload_UI;
	if(pEnemyReloadUI == nullptr) { return nullptr;}

	pEnemyReloadUI->SetPos(pos);	//�ʒu�ݒ�
	pEnemyReloadUI->SetSize(size);	//�T�C�Y�ݒ�

	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pEnemyReloadUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pEnemyReloadUI->Init();	//�������ݒ�
	return pEnemyReloadUI;
}
