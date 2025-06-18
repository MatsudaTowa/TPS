//=============================================
//
//ポーズのUI_コンティニュー[pause_select_continue.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_continue.h"

//=============================================
//コンストラクタ
//=============================================
CPauseSelectContinue::CPauseSelectContinue(int nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelectContinue::~CPauseSelectContinue()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelectContinue::Init()
{
	CPauseSelect::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CPauseSelectContinue::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelectContinue::Update()
{
	CPauseSelect::Update();
}

//=============================================
// 描画
//=============================================
void CPauseSelectContinue::Draw()
{
	CPauseSelect::Draw();
}

