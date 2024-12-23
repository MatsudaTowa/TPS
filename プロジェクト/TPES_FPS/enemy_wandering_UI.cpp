//=============================================
//
//敵の混乱のUI[enemy_wandering_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_wandering_UI.h"
#include "manager.h"

const std::string CEnemy_Wandering_UI::TEXTURE_NAME = "data\\TEXTURE\\wandering_UI.png";

//=============================================
//コンストラクタ
//=============================================
CEnemy_Wandering_UI::CEnemy_Wandering_UI(int nPriority):CEnemy_Reaction_UI(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Wandering_UI::~CEnemy_Wandering_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Wandering_UI::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CEnemy_Reaction_UI::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_Wandering_UI::Uninit()
{
	CEnemy_Reaction_UI::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy_Wandering_UI::Update()
{
	CEnemy_Reaction_UI::Update();
}

//=============================================
//描画
//=============================================
void CEnemy_Wandering_UI::Draw()
{
	CEnemy_Reaction_UI::Draw();
}
