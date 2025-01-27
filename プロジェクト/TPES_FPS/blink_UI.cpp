//=============================================
//
//ブリンク表示「blink_UI.cpp」
// Author松田永久
//
//=============================================
#include "blink_UI.h"

//桁ごとにずらす
const float CBlink_UI::DIGIT_SHIFT = 35.0f;

const D3DXVECTOR3 CBlink_UI::BOX_POS = { 470.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CBlink_UI::BOX_SIZE = { 50.0f, 50.0f };

const D3DXVECTOR3 CBlink_UI::ICON_POS = { 470.0f,665.0f,0.0f };
const D3DXVECTOR2 CBlink_UI::ICON_SIZE = { 40.0f, 40.0f };

const D3DXVECTOR3 CBlink_UI::NUMBER_POS = { 1000.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CBlink_UI::NUMBER_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CBlink_UI::KEY_UI_POS = { 470.0f,700.0f,0.0f };
const D3DXVECTOR2 CBlink_UI::KEY_UI_SIZE = { 40.0f, 20.0f };

//=============================================
//コンストラクタ
//=============================================
CBlink_UI::CBlink_UI():
m_BlinkUIPos({ 0.0f,0.0f,0.0f }),	//ブリンクのUI位置初期化
m_NumBlink(0),					//ブリンクの数初期化
m_pCurrentBlink(),				//現在のブリンクの数のポインタ初期化
m_pUIBox(),						//UIの枠初期化
m_pIcon(),						//アイコンの初期化
m_pkeyboard_UI()				//キーボードの初期化
{
}

//=============================================
//デストラクタ
//=============================================
CBlink_UI::~CBlink_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlink_UI::Init(CPlayer* player)
{
	m_BlinkUIPos = NUMBER_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//UIの枠生成
	if (m_pIcon == nullptr)
	{
		m_pIcon = CBlinkIcon::Create(ICON_POS, ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	//キーボードUIの枠生成
	if (m_pkeyboard_UI == nullptr)
	{
		m_pkeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CKeyboard_UI::KEY_LSHIFT);
	}

	//数字生成
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentBlink[nCnt] == nullptr)
		{
			m_pCurrentBlink[nCnt] = CNumber_2D::Create(m_BlinkUIPos, NUMBER_SIZE);
			//座標をずらす
			m_BlinkUIPos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlink_UI::Uninit()
{
	//UIの枠破棄
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	//キーボードUIのアイコン破棄
	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	//UIのアイコン破棄
	if (m_pkeyboard_UI != nullptr)
	{
		m_pkeyboard_UI->Uninit();
		m_pkeyboard_UI = nullptr;
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//数字破棄
		if (m_pCurrentBlink[nCnt] != nullptr)
		{
			m_pCurrentBlink[nCnt]->Uninit();
			m_pCurrentBlink[nCnt] = nullptr;
		}
	}

	delete this;
}

//=============================================
//更新
//=============================================
void CBlink_UI::Update()
{
}

//=============================================
//現在のブリンク状態代入
//=============================================
void CBlink_UI::SetCurrentBlink_UI(CPlayer* player)
{
	//if (player->GetSmoke())
	//{//スモークを使っていたら
	//	m_pIcon->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	//}
	//else if (!player->GetSmoke())
	//{//スモークを使っていなかったら
	//	m_pIcon->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//}
}

//=============================================
//何回ブリンクできるか代入
//=============================================
void CBlink_UI::SetNumber(int nParcent)
{
}

//=============================================
//リセット
//=============================================
void CBlink_UI::Reset()
{
}
