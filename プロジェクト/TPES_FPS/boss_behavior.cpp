//=============================================
//
//ボスのストラテジーパターン[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"
#include "wave_boss.h"
#include "player_test.h"

//=============================================
//コンストラクタ
//=============================================
CBossWandering::CBossWandering():m_MoveIdx(0), m_StopCnt(0), m_isMove()
{
	m_isMove = true;
}

//=============================================
//デストラクタ
//=============================================
CBossWandering::~CBossWandering()
{
}

//=============================================
//徘徊
//=============================================
void CBossWandering::Wandering(CBossEnemy* boss)
{
	if (m_isMove)
	{
		//移動先の情報取得(引数が移動先のポイントの配列番号)
		CMovePoint* pMovePoint = CWave_Boss::GetMovePoint(m_MoveIdx);

		//対象の位置への方向情報
		D3DXVECTOR3 point = { pMovePoint->GetPos().x - boss->GetPos().x,0.0f,pMovePoint->GetPos().z - boss->GetPos().z };

		// 目的地との距離を計算
		float distance = sqrtf(point.x * point.x + point.z * point.z);

		// 到達判定用の閾値
		const float threshold = 0.5f; // 距離が定数以下なら到達とする（必要に応じて調整）

		// まだ目的地に到達していない場合のみ移動処理を行う
		if (distance > threshold)
		{
			//対象物との角度計算
			float angle = atan2f(point.x, point.z);

			D3DXVECTOR3 move = boss->GetMove();

			move.x += sinf(angle) * boss->GetSpeed();
			move.z += cosf(angle) * boss->GetSpeed();
			//親クラスからrotを取得
			D3DXVECTOR3 rot = boss->GetRot();
			rot.y = angle + D3DX_PI;
			//rotを代入
			boss->SetRot(rot);
			//移動量代入
			boss->SetMove(move);
		}
		else
		{//到達していたら
			m_isMove = false;

			D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
			boss->SetMove(move);

			//次の移動先の抽選
			PickNextMovePoint(pMovePoint);
		}
	}
	else if (!m_isMove)
	{//動かない状態なら
		//指定フレーム分止まる
		StopCnt();
	}
}

//=============================================
//指定フレーム分止まる
//=============================================
void CBossWandering::StopCnt()
{
	++m_StopCnt;
	if (m_StopCnt > STOP_FRAME)
	{
		m_StopCnt = 0;
		m_isMove = true;
	}
}

//=============================================
//次の移動先の抽選
//=============================================
void CBossWandering::PickNextMovePoint(CMovePoint* pMovePoint)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, pMovePoint->GetNumPoint());
	//ランダムで位置指定
  	m_MoveIdx = number(random);
	if (m_MoveIdx >= pMovePoint->GetNumPoint())
	{
		m_MoveIdx = 0;
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CBossWandering::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n[ボス進む位置]%d"
		,m_MoveIdx );
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CBossChase::CBossChase()
{
}

//=============================================
//デストラクタ
//=============================================
CBossChase::~CBossChase()
{
}

//=============================================
//追跡
//=============================================
void CBossChase::Chase(CBossEnemy* boss, CObject* obj)
{
	CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(obj);

	//プレイヤーの位置への方向情報
	D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

	// 目的地との距離を計算
	float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

	// 到達判定用の閾値
	const float threshold = 200.0f; // 距離が定数以下なら到達とする 遠距離武器だから近づきすぎないように調整

	if (distance < boss->LOST_PLAYER_DISTANCE)
	{
		//プレイヤーに向かって動かす
		MovetoPlayer(distance, threshold, Vector, boss);
	}
	else
	{
		boss->ChangeState(new CWanderingState);
	}
	
}

//=============================================
//プレイヤーに向かって動かす
//=============================================
void CBossChase::MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss)
{
	// まだ目的地に到達していない場合のみ移動処理を行う
	if (distance > threshold)
	{
		//対象物との角度計算
		float angle = atan2f(Vector.x, Vector.z);

		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(angle) * boss->GetSpeed();
		move.z += cosf(angle) * boss->GetSpeed();
		//親クラスからrotを取得
		D3DXVECTOR3 rot = boss->GetRot();
		rot.y = angle + D3DX_PI;
		//rotを代入
		boss->SetRot(rot);
		//移動量代入
		boss->SetMove(move);
	}
	else
	{//到達していたら
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
		boss->SetMove(move);
	}
}

//=============================================
//コンストラクタ
//=============================================
CBossAttack::CBossAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CBossAttack::~CBossAttack()
{
}

//=============================================
//攻撃
//=============================================
void CBossAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{

}

//=============================================
//ボスのポインターを引数にしてオーバーロード
//=============================================
void CBossAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CBossEnemy* boss)
{
	CEnemyAttack::Attack(Allegiance, type, boss);
}
