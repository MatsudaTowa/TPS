//=============================================
//
//プレイヤーのUIの枠[player_UI_box.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_UI_box.h"
#include "manager.h"

const std::string CPlayerUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box.png";

//=============================================
//コンストラクタ
//=============================================
CPlayerUIBox::CPlayerUIBox(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerUIBox::~CPlayerUIBox()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayerUIBox::Init()
{
	//親クラスの初期化
	CObject2D::Init();

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayerUIBox::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayerUIBox::Update()
{
	//親クラスの更新
	CObject2D::Update();

	SetVtx(1.0f);

}

//=============================================
//描画
//=============================================
void CPlayerUIBox::Draw()
{
	//親クラスの描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CPlayerUIBox* CPlayerUIBox::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CPlayerUIBox*pUIBox = new CPlayerUIBox;
	
	if(pUIBox == nullptr) {return nullptr;}

	//座標代入
	pUIBox->SetPos(pos);

	//サイズ代入
	pUIBox->SetSize(size);

	//色代入
	pUIBox->SetColor(col);

	pUIBox->SetType(OBJECT_TYPE_UI_BOX);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//pUIBox->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pUIBox->Init();

	return pUIBox;
}
