//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"

//モデルパス
const char* CBlock::MODEL_NAME = "data\\MODEL\\c.x";

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlock::Init()
{
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CBlock::Update()
{
	//親クラスの更新処理
	CObjectX::Update();
}

//=============================================
//描画
//=============================================
void CBlock::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスの描画処理
	CObjectX::Draw();

	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;

	//nullならnullを返す
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetInstance()->GetModel();
	CTexture* pTex = CManager::GetInstance()->GetTexture();

	pBlock->m_type = type;
	pBlock->SetPos(pos); //pos設定
	pBlock->SetRot(rot); //pos設定
	pBlock->m_nLife = nLife; //寿命代入
	pBlock->m_bBreak = bBreak; //壊せるかどうか
	//pBlock->BindTexture(m_pTextureTemp);

	//Xファイル読み込み
	pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pBlock->SetType(OBJECT_TYPE_BLOCK); //タイプ設定
	pBlock->Init();
	
	return pBlock;
}