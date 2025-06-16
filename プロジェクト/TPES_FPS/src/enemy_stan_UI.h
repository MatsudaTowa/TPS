//=============================================
//
//敵の混乱のUI[enemy_stan_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "enemy_reaction_UI.h"

#ifndef _ENEMY_STAN_UI_H_ //これが定義されてないとき

#define _ENEMY_STAN_UI_H_

class CEnemy_Stan_UI : public CEnemy_Reaction_UI
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CEnemy_Stan_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CEnemy_Stan_UI()override;
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
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};

#endif