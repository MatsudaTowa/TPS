//=============================================
//
//ゲームスコア処理「game_scorer.h」
// Author松田永久
//
//=============================================
#ifndef _GAME_SCORE_H_ //これが定義されてないとき
#define _GAME_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//スコアクラス
//=============================================
class CGameScore : public CScore
{
public:
	static const float DIGIT_SHIFT;
	CGameScore();
	~CGameScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ

	CPlayerUIBox* m_pPlayerUIBox;
};

#endif // DEBUG
