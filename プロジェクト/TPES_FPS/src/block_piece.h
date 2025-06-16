//=============================================
//
//�u���b�N�̔j��[block_piece.h]
//Author Matsuda Towa
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

	/**
	 * @brief �R���X�g���N�^
	 * @param �v���C�I���e�B
	 */
	CBlock_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBlock_Piece()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I�� 
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;

	/**
	 * @brief �u���b�N�̔j�А���
	 * @param �ʒu
	 * @param ����
	 * @param �T�C�Y
	 * @param ���������ǂ���
	 * @return 
	 */
	static CBlock_Piece* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 scale,bool isMove);
private:
	static constexpr float SHIFT_X_MAX = 50.0f;		//X�̍ő僀�[�u��
	static constexpr float SHIFT_X_MIN = -50.0f;	//X�̍ŏ����[�u��

	static constexpr float SHIFT_Z_MAX = 50.0f;		//Z�̍ő僀�[�u��
	static constexpr float SHIFT_Z_MIN = -50.0f;	//Z�̍ŏ����[�u��
	PIECE_SHAPE m_shape;	//�j�Ђ̌`��
};

//=============================================
//�u���b�N�̓������j�ЃN���X
//=============================================
class CMove_Piece :public CBlock_Piece
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMove_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMove_Piece()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
private:
	static const int LIFE = 120;				//����
	static const int RAND_RANGE = 101;			//�����_���̎Z�o�͈�
	static constexpr float MIN_MOVE = 5.0f;		//�ړ��ʂ̍Œ�l
	static constexpr float MOVE_RANGE = 10.0f;	//�ړ��ʂ̎Z�o�͈�
	D3DXVECTOR3 m_move;							//�ړ���
	int m_nLife;								//�̗�
};

//=============================================
//�u���b�N�̓������Ȃ��j�ЃN���X
//=============================================
class CStack_Piece :public CBlock_Piece
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CStack_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CStack_Piece()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
private:
};
#endif