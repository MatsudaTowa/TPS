//=============================================
//
//�A�j���[�V��������2D�I�u�W�F�N�g[move_texture.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_TEXTURE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOVE_TEXTURE_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�A�j���[�V����2D�N���X
//=============================================
class CObject2D_Anim : public CObject2D
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CObject2D_Anim(int nPriority);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CObject2D_Anim()override;

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
	 * @brief �A�j���[�V�������W�ݒ�
	 * @param [in]�e�N�X�`�����W
	 * @param [in]�e�N�X�`���ړ���
	 */
	void AnimationTex(D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);

	/**
	 * @brief �A�j���[�V�����t���[�����
	 * @param [in]�A�j���[�V�����t���[��
	 */
	inline void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	/**
	 * @brief �e�N�X�`���ړ��ʑ��
	 * @param [in]�e�N�X�`���ړ���
	 */
	inline void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}

	/**
	 * @brief �A�j���[�V�����t���[���擾
	 * @return �A�j���[�V�����t���[��
	 */
	inline int GetAnimFrame()
	{
		return m_nAnimFrame;
	}
	
	/**
	 * @brief �e�N�X�`���ړ��ʎ擾
	 * @return �e�N�X�`���ړ���
	 */
	inline D3DXVECTOR2& GetTexMove()
	{
		return m_tex_move;
	}

private:
	//�A�j���[�V����
	int m_nAnimFrame; //�A�j���[�V�����t���[��
	int m_nAnimCnt; //�A�j���[�V�����J�E���g
	D3DXVECTOR2 m_tex_move; //tex�ړ���

};
#endif