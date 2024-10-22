//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BLOCK_H_
#include "main.h"
#include "objectX.h"

class CBlock : public CObjectX
{
public:
	static const std::string MODEL_NAME;	//���f���̖��O
	static const std::string WOOD_MODEL_NAME;	//���f���̖��O
	static const std::string AZUMAYA_MODEL_NAME;	//���f���̖��O
	static const std::string DANGOYA_MODEL_NAME;	//���f���̖��O

	static const int BLOCK_PRIORITY = 3; //�`�揇
	typedef enum
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
		BLOCKTYPE_WOOD,
		BLOCKTYPE_AZUMAYA,
		BLOCKTYPE_DANGOYA,
		BLOCKTYPE_MAX,
	}BLOCKTYPE;

	CBlock(int nPriority = BLOCK_PRIORITY);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�u���b�N�쐬
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,bool bBreak);
private:

	BLOCKTYPE m_type;
	bool m_bBreak; //�󂹂邩�ǂ���
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh; //���b�V�����
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����;
};
#endif