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
CReticle::CReticle():m_pCrosshair(nullptr),
m_ReticlePos({0.0f,0.0f,0.0f}),		//���e�B�N���̈ʒu
m_ReticleSize({0.0f,0.0f,0.0f}),	//���e�B�N���̃T�C�Y
m_ReticleCol({1.0f,1.0f,1.0f,1.0f})	//���e�B�N���̐F
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
}