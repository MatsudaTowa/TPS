//=============================================
//
//�u���b�N�̔j��[block_piece.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_PIECE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BLOCK_PIECE_H_
#include "main.h"
#include "objectX.h"
#include "manager.h"

//=============================================
//�u���b�N�̔j�ЃN���X
//=============================================
class CBlock_Piece : public CObjectX
{
public:
	static const int BLOCK_PRIORITY = 10; //�`�揇

	enum PIECE_SHAPE
	{
		PIECE_SHAPE_0 = 0,
		PIECE_SHAPE_1,
		PIECE_SHAPE_2,
		PIECE_SHAPE_MAX,
	};

	static const char* MODEL_NAME[PIECE_SHAPE_MAX];	//���f���̖��O

	CBlock_Piece(int nPriority = BLOCK_PRIORITY);
	~CBlock_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�u���b�N�쐬
	static CBlock_Piece* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 scale,bool isMove);
private:
	static constexpr float SHIFT_X_MAX = 50.0f;
	static constexpr float SHIFT_X_MIN = -50.0f;

	static constexpr float SHIFT_Z_MAX = 50.0f;
	static constexpr float SHIFT_Z_MIN = -50.0f;
	PIECE_SHAPE m_shape;
};

//=============================================
//�u���b�N�̓������j�ЃN���X
//=============================================
class CMove_Piece :public CBlock_Piece
{
public:
	CMove_Piece(int nPriority = BLOCK_PRIORITY);
	~CMove_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const int LIFE = 120;				//����
	static const int RAND_RANGE = 101;			//�����_���̎Z�o�͈�
	static constexpr float MIN_MOVE = 5.0f;		//�ړ��ʂ̍Œ�l
	static constexpr float MOVE_RANGE = 10.0f;	//�ړ��ʂ̎Z�o�͈�
	D3DXVECTOR3 m_move;
	int m_nLife;
};

//=============================================
//�u���b�N�̓������Ȃ��j�ЃN���X
//=============================================
class CStack_Piece :public CBlock_Piece
{
public:
	CStack_Piece(int nPriority = BLOCK_PRIORITY);
	~CStack_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif