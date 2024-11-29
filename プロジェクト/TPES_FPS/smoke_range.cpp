//=============================================
//
//スモーク範囲処理[somoke_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_range.h"
#include "manager.h"

//モデルパス
const char* CSmokeRange::MODEL_NAME = "data\\MODEL\\Container000.x";

//=============================================
//コンストラクタ
//=============================================
CSmokeRange::CSmokeRange(int nPriority):CObjectX(nPriority), m_nLife(0)
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeRange::~CSmokeRange()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeRange::Init()
{
	CObjectX::Init();
	m_nLife = CSmoke::SMOKE_LIFE;
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeRange::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeRange::Update()
{
	CObjectX::Update();
	if (m_nLife > 0)
	{
		--m_nLife;
	}
	else
	{
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmokeRange::Draw()
{
#ifdef _DEBUG
	CObjectX::Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(1.0f, 3.0f, 1.0f));
#endif // _DEBUG
}

//=============================================
//生成
//=============================================
CSmokeRange* CSmokeRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CSmokeRange* pSmokeRange = new CSmokeRange;

	if (pSmokeRange == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pSmokeRange->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pSmokeRange->SetPos(pos);
	pSmokeRange->SetRot(rot);
	pSmokeRange->Init();
	pSmokeRange->SetType(OBJECT_TYPE_SMOKE_RANGE);

	return pSmokeRange;
}
