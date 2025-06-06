//=============================================
// 
//敵が徘徊する際に向かうポイント[move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_ //これが定義されてないとき

#define _MOVE_POINT_
#include "main.h"
#include "billboard.h"

//=============================================
// 探索ポイントクラス
//=============================================
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

	//数取得
	static int& GetNumPoint()
	{
		return m_NumPoint;
	};
private:
	static constexpr float POINT_SIZE = 10.0f; //サイズ

	static int m_NumPoint; //何個あるか
};
#endif