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
	static const int BLOCK_PRIORITY = 10; //�`�揇
	enum BLOCKTYPE
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
		BLOCKTYPE_WOOD,
		BLOCKTYPE_AZUMAYA,
		BLOCKTYPE_DANGOYA,
		BLOCKTYPE_MESH,
		BLOCKTYPE_MAX,
	};

	CBlock(int nPriority = BLOCK_PRIORITY);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void CreatePiece();
	void Draw()override;
	//�u���b�N�쐬
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,bool bBreak);
private:
	static const char* MODEL_NAME;	//���f���̖��O

	static const int NUM_PIECE = 5; //��ꂽ�ۂɐ�������s�[�X��
	static const int NUM_SMOKE = 30; //��ꂽ�ۂɐ�������X���[�N��

	static constexpr float PIECE_ROTATION_MAX = 3.0f; //��]�͈͍ő�l
	static constexpr float PIECE_ROTATION_MIN = 0.0f; //��]�͈͍ŏ��l

	static const D3DXCOLOR SMOKE_COLOR; //��ꂽ�ۂɐ�������X���[�N�̐F

	static const D3DXVECTOR3 MOVE_PIECE_SCALE; //�����s�[�X�̃X�P�[��
	static const D3DXVECTOR3 STACK_PIECE_SCALE; //�c��s�[�X�̃X�P�[��

	BLOCKTYPE m_type;
	bool m_bBreak; //�󂹂邩�ǂ���
	int m_nLife;
};
#endif