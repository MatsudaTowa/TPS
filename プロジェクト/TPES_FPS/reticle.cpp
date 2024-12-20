//=============================================
//
//���e�B�N��[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CReticle::CReticle():
m_pCrosshair(nullptr),				//�N���X�w�A�̃|�C���^�[
m_pCenterDot(nullptr),				//�Z���^�[�h�b�g�̃|�C���^�[
m_pHitMaker(nullptr),				//�q�b�g�}�[�J�[�̃|�C���^�[
m_ReticlePos({0.0f,0.0f,0.0f}),		//���e�B�N���̈ʒu
m_ReticleSize({0.0f,0.0f,0.0f}),	//���e�B�N���̃T�C�Y
m_ReticleCol({0.0f,1.0f,1.0f,1.0f})	//���e�B�N���̐F
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CReticle::~CReticle()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->Uninit();
		m_pCrosshair = nullptr;
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->Uninit();
		m_pCenterDot = nullptr;
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->Uninit();
		m_pHitMaker = nullptr;
	}
}

//=============================================
//������
//=============================================
HRESULT CReticle::Init()
{
	if (m_pCrosshair == nullptr)
	{
		m_pCrosshair = CCrossHair::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, m_ReticleCol);
	}

	if (m_pCenterDot == nullptr)
	{
		m_pCenterDot = CCenterDot::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, m_ReticleCol);
	}

	if (m_pHitMaker == nullptr)
	{
		m_pHitMaker = CHitMaker::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, {1.0f,1.0f,1.0f,0.0f});
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CReticle::Uninit()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->Uninit();
		m_pCrosshair = nullptr;
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->Uninit();
		m_pCenterDot = nullptr;
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->Uninit();
		m_pHitMaker = nullptr;
	}

	delete this;
}

//=============================================
//�X�V
//=============================================
void CReticle::Update()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->SetPos(m_ReticlePos);
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->SetPos(m_ReticlePos);
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->SetPos(m_ReticlePos);

	}
}