//=============================================
// 
//敵が徘徊する際に向かうポイント[move_point.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "move_point.h"

//何番目の地点か
int CMovePoint::m_NumPoint = 0;

//=============================================
//コンストラクタ
//=============================================
CMovePoint::CMovePoint(int nPriority):CBillboard(nPriority) ,m_Idx(0)
{
	++m_NumPoint;
}

//=============================================
//デストラクタ
//=============================================
CMovePoint::~CMovePoint()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMovePoint::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CMovePoint::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CMovePoint::Update()
{
	//親クラスの更新処理
	CObject3D::Update();
}

//=============================================
//描画
//=============================================
void CMovePoint::Draw()
{
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CMovePoint* CMovePoint::Create(D3DXVECTOR3 pos)
{
	CMovePoint* pMovePoint = new CMovePoint;
	if(pMovePoint == nullptr){ return nullptr; }

	//位置の設定
	pMovePoint->SetPos(pos);

	//自分の番号を割り当て
	pMovePoint->SetIdx(m_NumPoint);

	pMovePoint->Init();

	return pMovePoint;
}
