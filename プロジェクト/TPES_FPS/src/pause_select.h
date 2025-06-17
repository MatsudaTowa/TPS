//=============================================
//
//ブリンクの表記[blink_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_H_ //これが定義されてないとき

#define _PAUSE_SELECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ポーズ選択UIクラス
//=============================================
class CPauseSelect : public CObject2D
{
public:
	static const int PRIORITY = 21;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseSelect(int nPriority = PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CPauseSelect()override;
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
	 * @return ポーズのUIポインタ
	 */
	static CPauseSelect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif