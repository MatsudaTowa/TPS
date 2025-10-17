//=============================================
//
//�v���C���[UI�}�l�[�W���[[player_UI_maneger.cpp]
//Auther MatsudaTowa
//
//=============================================
#include "player_UI_manager.h"

//�e��UI�̈ʒu
const D3DXVECTOR3 CPlayerUIManager::GUN_UI_POS = { 1150.0f, 665.0f, 0.0f };

//�e��UI�̃T�C�Y
const D3DXVECTOR2 CPlayerUIManager::GUN_UI_SIZE = { 70.0f,30.0f };
//=============================================
// �R���X�g���N�^
//=============================================
CPlayerUIManager::CPlayerUIManager():
	m_pAmmoUI(nullptr),				//�e��UI
	m_pBlinkUI(nullptr),			//�u�����NUI
	m_pGunIcon(nullptr),			//�e�̃A�C�R��
	m_pLifeUI(nullptr),				//�̗�UI
	m_pReloadUI(nullptr),			//�����[�hUI
	m_pSmokeUI(nullptr),			//�X���[�NUI
	m_pUltUI(nullptr)				//�E���gUI
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPlayerUIManager::~CPlayerUIManager()
{
}

//=============================================
// �I��
//=============================================
void CPlayerUIManager::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->Uninit();
		m_pBlinkUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pUltUI->Uninit();
		m_pUltUI = nullptr;
	}
	if (m_pGunIcon != nullptr)
	{
		m_pGunIcon->Uninit();
		m_pGunIcon = nullptr;
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->Uninit();
		m_pSmokeUI = nullptr;
	}
	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Uninit();
		m_pReloadUI = nullptr;
	}
}

//=============================================
// UI�̐���
//=============================================
void CPlayerUIManager::CreateUI(CActivePlayer* player)
{
	if (m_pGunIcon == nullptr)
	{
		m_pGunIcon = CGunIcon::Create(GUN_UI_POS, GUN_UI_SIZE, COLOR_WHITE, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
	}
	//�c�e��������
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();

		m_pAmmoUI->SetDefaultAmmo_UI(player->GetGun()->GetAmmo());
	}
	//�̗�UI������
	if (m_pLifeUI == nullptr)
	{
		m_pLifeUI = new CLife_UI;

		m_pLifeUI->Init();
	}
	//�u�����NUI������
	if (m_pBlinkUI == nullptr)
	{
		m_pBlinkUI = new CBlink_UI;

		m_pBlinkUI->Init();
	}
	//�E���gUI������
	if (m_pUltUI == nullptr)
	{
		m_pUltUI = new CUlt_UI;

		m_pUltUI->Init(player);
	}

	if (m_pSmokeUI == nullptr)
	{
		m_pSmokeUI = new CSmoke_UI;
		m_pSmokeUI->Init(player);
	}
}

//=============================================
// UI�ݒ�
//=============================================
void CPlayerUIManager::SetUI(CActivePlayer* player)
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetCurrentAmmo_UI(player->GetGun()->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(player->GetLife());
	}

	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->SetCurrentBlink_UI(player);
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->SetCurrentSmoke_UI(player);
	}
}
