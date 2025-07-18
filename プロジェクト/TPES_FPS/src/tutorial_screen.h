//=============================================
//
//チュートリアルスクリーン[tutorial_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_SCREEN_H_ //これが定義されてないとき

#define _TUTORIAL_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
// チュートリアル画面クラス
//=============================================
class CTutorial_Screen : public CObject2D
{
public:
	enum TUTORIAL_UI
	{
		UI_NONE = 0,
		UI_TUTORIAL_TXT,
		UI_TITLE_PRESS_BUTTON,
		UI_TITLE_MAX,
	};
	static const std::string TXT_TEXTURE_NAME;	//テクスチャの名前
	static const std::string BUTTON_A_TEXTURE_NAME;	//テクスチャの名前
	static const std::string BUTTON_ENTER_TEXTURE_NAME;	//テクスチャの名前
	static const int TUTORIAL_SCREEN_PRIORITY = 20;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CTutorial_Screen(int nPriority = TUTORIAL_SCREEN_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CTutorial_Screen()override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init()override;
	/**
	 * @brief 終了
	 */
	void Uninit()override;
	/**
	 * @brief 更新
	 */
	void Update()override;
	/**
	 * @brief 描画
	 */
	void Draw()override;
	/**
	 * @brief 生成
	 * @param [in]位置
	 * @param [in]サイズ
	 * @param [in]タイプ
	 * @return チュートリアルUIポインタ
	 */
	static CTutorial_Screen* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TUTORIAL_UI type);
private:
	TUTORIAL_UI m_UItype;
};
#endif
