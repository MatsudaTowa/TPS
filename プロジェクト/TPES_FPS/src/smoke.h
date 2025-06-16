//=============================================
//
//�X���[�N����[somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_H_

//=============================================
// �X���[�N�N���X
//=============================================
class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //�e�N�X�`���̖��O
	static const int SMOKE_LIFE = 300; //�X���[�N�̎�������

	static const int SMOKE_PRIORITY = 10; //�`�揇

	enum SMOKE_TYPE
	{
		SMOKE_TYPE_TACTICAL	= 0,
		SMOKE_TYPE_BROKEN
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSmoke(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSmoke()override;
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
	 * @brief ����
	 * @param [in]�ʒu
	 * @param [in]�X���[�N�̃^�C�v
	 * @return �X���[�N�|�C���^
	 */
	static CSmoke* Create(D3DXVECTOR3 pos, SMOKE_TYPE type);

	/**
	 * @brief �ړ��ʐݒ�
	 * @param [in]�ړ���
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	/**
	 * @brief �ړ��ʎ擾
	 * @return �ړ���
	 */
	inline D3DXVECTOR3& GetMove()
	{
		return m_move;
	}

private:
	static constexpr float FADE_VALUE = 0.1f;  //�A���t�@�l������

	/**
	 * @brief �ړ�����
	 */
	void Move();

	/**
	 * @brief �t�F�[�h�A�E�g
	 */
	void FadeOut();

	int m_nLife;
	D3DXVECTOR3 m_move;
};

#endif