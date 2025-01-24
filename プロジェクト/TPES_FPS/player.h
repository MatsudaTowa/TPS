//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _player_H_ //これが定義されてないとき

#define _player_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "reticle.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "player_behavior.h"
#include "enemy.h"
#include "hit_camera_effect.h"
#include "gun_icon.h"
#include "player_state.h"
#include "ult.h"
#include "smoke_UI.h"

class CPlayerState;
class CPlayerSliding;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;

//プレイヤークラス
class CPlayer:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //パーツ数
	static const int MAX_KEY = 20; //キー最大数
	static const int PLAYER_LIFE = 150; //体力
	static const int PLAYER_PRIORITY = 8; //描画順
	static const int PARTS_PARENT[NUM_PARTS]; //パーツ数

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //スポーン位置
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //スポーン方向
	//モーションの種類の列挙
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	}Motion_Type;

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //当たり判定

	void ResetRot(); //方向のリセット

	void ColisionEnemy(); //敵との当たり判定

	void ChangeDamageState(); //TODOキャラクターにまとめろ

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //プレイヤー入力処理

	void ChangePlayerState(CPlayerState* state);

	void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	void SetSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	bool& GetSmoke()
	{
		return m_isSmoke;
	}

	CReticle* m_Raticle;

	CUlt* m_pUlt;

	CPlayerSliding* m_pSliding;

	CPlayerState* m_pPlayerState;
private:

	//プレイヤーの移動関連
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const int MAX_JUMPCNT; //ジャンプ回数
	static const int IGNORE_COLLISION_FRAME; //当たり判定無視フレーム
	static const int SMOKE_RECAST_FRAME; //スモーク復活フレーム
	static const float DEADZONE_Y; //これを過ぎたらプレイヤー破棄
	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //デフォルトのアサルトのリロードフレーム数
	static const int DEFAULT_AR_DAMAGE = 10; //デフォルトのアサルトのダメージ

	void SetUI(); //UI設定
	void ReSpawn(); //リスポーン
	static CAmmo_UI* m_pAmmoUI;
	static CLife_UI* m_pLifeUI;

	CUlt_UI* m_pUltUI;
	CSmoke_UI* m_pSmokeUI;

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	CGunIcon* m_pGunIcon;

	CHitCameraEffect* m_pHitCameraEffect;

	void DebugPos();

	int m_IgnoreColisionCnt;

	int m_SmokeRecastCnt;

	int m_DeathCnt;

	bool m_isEnemyColision; //エネミーとの判定をとるか

	bool m_isRelorad; //リロードするかどうか

	bool m_isSmoke; //スモークを使ったか
};
#endif