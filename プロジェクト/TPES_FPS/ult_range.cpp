//=============================================
//
//ウルト範囲処理[ult_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_range.h"
#include "manager.h"
#include "enemy.h"
#include "object.h"

const float CUltRange::RADIUS = 20.0f;

//=============================================
//コンストラクタ
//=============================================
CUltRange::CUltRange() :m_nLife(0), m_pos({0.0f,0.0f,0.0f})
{
}

//=============================================
//デストラクタ
//=============================================
CUltRange::~CUltRange()
{
}

//=============================================
//初期化
//=============================================
HRESULT CUltRange::Init()
{
	m_nLife = LIFE;
	return S_OK;
}

//=============================================
//終了
//=============================================
void CUltRange::Uninit()
{
	delete this;
}

//=============================================
//更新
//=============================================
void CUltRange::Update()
{
	--m_nLife;

	if (m_nLife > 0)
	{
		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//敵との当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(pObj);

					CColision::COLISION ColisionCheck;
					
					ColisionCheck = CManager::GetInstance()->GetColision()->CheckColisionCircle(m_pos,RADIUS,enemy->GetPos());

					if (ColisionCheck != CColision::COLISION::COLISON_NONE)
					{
						enemy->Damage(MAX_DAMAGE);
					}
				}
			}
		}
	}
}

//=============================================
//生成
//=============================================
CUltRange* CUltRange::Create(D3DXVECTOR3 pos)
{
	CUltRange* pRange = new CUltRange;

	//何も入ってなかったらreturn
	if (pRange == nullptr) { return nullptr; }

	pRange->m_pos = pos;
	pRange->Init();

	return pRange;
}
