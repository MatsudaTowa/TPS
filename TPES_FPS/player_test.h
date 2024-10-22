//=============================================
//
//3DTemplate[player_test.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_TEST_H_ //これが定義されてないとき

#define _PLAYER_TEST_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
//プレイヤークラス
class CPlayer_test:public CCharacter
{
public:
	static const int NUM_PARTS = 10; //パーツ数
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION	= 3;
	static const int PLAYER_PRIORITY = 8; //描画順
	static const int PARTS_PARENT[NUM_PARTS]; //パーツ数

	CPlayer_test(int nPriority = PLAYER_PRIORITY);
	~CPlayer_test();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//プレイヤー作成
	static CPlayer_test* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //当たり判定

private:

	//プレイヤーの移動関連
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEFAULT_JUMP; //通常時のジャンプ力
	static const int MAX_JUMPCNT; //ジャンプ回数
	static const int NUM_MOTION; //モーションの数
	static const float DEADZONE_Y; //これを過ぎたらプレイヤー破棄

	void ReSpawn(); //リスポーン
	void PlayerMove(); //プレイヤー移動処理

	int m_nJumpCnt; //ジャンプカウント

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数

	//モーションの種類の列挙
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	}Motion_Type;

	Motion_Type m_Motion; //モーションの種類

	void DebugPos();

};
#endif