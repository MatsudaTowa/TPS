//=============================================
//
//通常の敵の処理[normal_enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_H_ //これが定義されてないとき

#define _NORMAL_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"

//=============================================
//通常のエネミークラス
//=============================================
class CNormalEnemy :public CEnemy
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int DEFAULT_LIFE = 50; //ライフ

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	~CNormalEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
private:

	//エネミーの移動関連
	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ
	static const int DEFAULT_AR_RELOAD_FRAME = 120; //デフォルトのアサルトのリロードフレーム数
	static const int DEFAULT_AR_DAMAGE = 3; //デフォルトのアサルトのダメージ

	Motion_Type m_Motion; //モーションの種類
};

#endif