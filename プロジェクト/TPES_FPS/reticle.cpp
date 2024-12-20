//=============================================
//
//レティクル[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CReticle::CReticle():m_pCrosshair(nullptr),
m_ReticlePos({0.0f,0.0f,0.0f}),		//レティクルの位置
m_ReticleSize({0.0f,0.0f,0.0f}),	//レティクルのサイズ
m_ReticleCol({1.0f,1.0f,1.0f,1.0f})	//レティクルの色
{
}

//=============================================
//デストラクタ
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
//初期化
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
//終了
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
//更新
//=============================================
void CReticle::Update()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->SetPos(m_ReticlePos);
	}
}