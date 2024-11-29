//=============================================
//
//スモーク処理[somoke.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke.h"

//=============================================
//コンストラクタ
//=============================================
CSmoke::CSmoke(int nPriority) : CBillboard(nPriority),m_nLife(0),m_move({0.0f,0.0f,0.0f})
{
}

//=============================================
//デストラクタ
//=============================================
CSmoke::~CSmoke()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmoke::Init()
{
	CObject3D::Init();
	m_nLife = SMOKE_LIFE; //ライフ設定
	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmoke::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CSmoke::Update()
{
	CObject3D::Update();

	if (m_nLife > 0)
	{
		--m_nLife;
		D3DXVECTOR3 pos = GetPos();

		pos += m_move;

		SetPos(pos);
	}
	else
	{
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmoke::Draw()
{
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CSmoke* pSmoke = new CSmoke;

	if(pSmoke == nullptr) {return nullptr;}

	pSmoke->SetPos(pos);
	pSmoke->m_move = move;
	pSmoke->SetRot(rot);
	pSmoke->SetSize(size);
	pSmoke->Init();
	return pSmoke;
}
