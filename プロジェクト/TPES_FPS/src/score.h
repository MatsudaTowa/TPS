//=============================================
//
//スコア処理「scorer.h」
// Author松田永久
//
//=============================================
#ifndef _SCORE_H_ //これが定義されてないとき
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"

//=============================================
//スコアクラス
//=============================================
class CScore
{
public:
	CScore();
	virtual ~CScore();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	void AddScore(int nValue);
	void ExportScore(const std::string& FileName); //スコア書き出し
	void Reset();

	int m_nScore; //スコアの値
	void SetScore(int nScore);

	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	inline void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	inline void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	//表示座標取得
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	//表示サイズ取得
	inline D3DXVECTOR2& GetSize()
	{
		return m_size;
	}

	//座標をずらす値を取得
	inline float& GetDigitShift()
	{
		return m_DigitShift;
	}
private:
	static const int NUM_DIGIT = 6;  //桁数

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
	CNumber_2D* m_pNumber[NUM_DIGIT];

	float m_DigitShift;
};
#endif // DEBUG