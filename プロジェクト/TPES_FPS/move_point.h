//=============================================
// 
//敵が徘徊する際に向かうポイント[move_point.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_ //これが定義されてないとき

#define _MOVE_POINT_
#include "main.h"
#include "billboard.h"

class CMovePoint : public CBillboard
{
public:
	static const int POINT_PRIORITY = 8; //描画順

	CMovePoint(int nPriority = POINT_PRIORITY);
	~CMovePoint() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMovePoint* Create(D3DXVECTOR3 pos);

	//番号設定
	void SetIdx(int Idx)
	{
		m_Idx = Idx;
	}

	//番号取得
	int& GetIdx()
	{
		return m_Idx;
	}

private:
	int m_Idx; //何番目の地点か
	static int m_NumPoint; //何個あるか
};
#endif