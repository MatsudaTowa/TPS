//=============================================
// 
//親子関係のパーツ[model.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MODEL_PARTS_H_ //これが定義されてないとき

#define _MODEL_PARTS_H_
#include "main.h"
#include "objectX.h"
#include "block.h"

//=============================================
// モデルパーツクラス
//=============================================
class CModel_Parts
{
public:
	static const int MAX_MODEL = 256; //モデルの数

	//モデル情報構造体定義
	struct MODEL_INFO
	{
		LPD3DXMESH pMesh; //メッシュ情報
		LPD3DXBUFFER pBuffMat; //マテリアル情報
		DWORD dwNumMat; //マテリアル数;
		char* ModelName; //モデルネーム保存用
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X軸に当たっている
		bool bColision_Y; //Y軸に当たっている
		bool bColision_Z; //Z軸に当たっている

		float Radius;
		CBlock* pBlock;
	};

	CModel_Parts();
	~CModel_Parts();
	void Unload(); //モデル破棄
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);
	void Draw();
	void Draw(D3DXCOLOR col);

	void ConversionMtxWorld();

	//パーツ生成
	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,char* pModel_Path);

	//ワールドマトリックスの代入
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//位置代入
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	};

	//Tポーズ時の位置代入
	inline void SetTPos(D3DXVECTOR3 Tpos)
	{
		m_Tpos = Tpos;
	};

	//過去の位置代入
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	};

	//方向代入
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	};

	//Tポーズ時の方向代入
	inline void SetTRot(D3DXVECTOR3 Trot)
	{
		m_Trot = Trot;
	};

	//当たったブロック情報代入
	inline void SetColisionBlockInfo(ColisionBlockInfo ColisionBlockInfo)
	{
		m_ColisionBlockInfo = ColisionBlockInfo;
	}

	//親パーツの設定
	inline void SetParent(CModel_Parts* pParent)
	{
		m_pParent = pParent;
	}

	//モデルの番号設定
	inline void SetIdx(int nIdx)
	{
		m_nIdx = nIdx;
	}

	//親番号の設定
	inline void SetParentIdx(int nParent)
	{
		m_nIdxModelParent = nParent;
	}

	//位置取得
	inline D3DXVECTOR3 GetPos()
	{
		return m_pos;
	};

	//Tポーズ時の位置取得
	inline D3DXVECTOR3 GetTPos()
	{
		return m_Tpos;
	};

	//過去の位置取得
	inline D3DXVECTOR3 GetOldPos()
	{
		return m_oldpos;
	};

	//方向取得
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	};

	//Tポーズ時の方向取得
	inline D3DXVECTOR3 GetTRot()
	{
		return m_Trot;
	};

	//最小値取得
	inline D3DXVECTOR3 GetMin()
	{
		return m_minpos;
	}

	//最大値取得
	inline D3DXVECTOR3 GetMax()
	{
		return m_maxpos;
	}

	//モデルの番号取得
	inline int GetIdx()
	{
		return m_nIdx;
	}

	//モデルの親番号取得
	inline int GetParentIdx()
	{
		return m_nIdxModelParent;
	}

	//当たったブロック情報取得
	inline ColisionBlockInfo& GetColisionBlockInfo()
	{
		return m_ColisionBlockInfo;
	}

	//ワールドマトリックス取得
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	//モデル情報取得
	inline MODEL_INFO GetModelInfo(int nIdx)
	{
		return m_ModelInfo[nIdx];
	}

private:
	LPDIRECT3DTEXTURE9 m_pTexture[256]; //テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //モデル情報

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Tpos;
	D3DXVECTOR3 m_Trot;
	int m_nIdx; //何番目のパーツか
	int m_nIdxModelParent; //親のインデックス

	D3DXVECTOR3 m_minpos; //pos最小値
	D3DXVECTOR3 m_maxpos; //pos最大値
	D3DXVECTOR3 m_oldpos;
	int m_nNumAll; //モデル総数

	CModel_Parts*m_pParent; //親パーツへのポインタ
	ColisionBlockInfo m_ColisionBlockInfo; //当たった軸

};
#endif