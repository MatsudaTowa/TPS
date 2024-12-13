//=============================================
//
//2DTemplate[move_texture.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MOVE_TEXTURE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOVE_TEXTURE_H_
#include "main.h"
#include "object2D.h"

//�����_���[�N���X
class CObject2D_Anim : public CObject2D
{
public:
	CObject2D_Anim(int nPriority);
	~CObject2D_Anim()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�A�j���[�V��������
	void AnimationTex(D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);
	//�A�j���[�V�����t���[�����
	void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	//�e�N�X�`���ړ��ʂ̑��
	void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}

	//�A�j���[�V�����t���[���擾
	int GetAnimFrame();
	
	//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2& GetTexMove();

private:
	//�A�j���[�V����
	int m_nAnimFrame; //�A�j���[�V�����t���[��
	int m_nAnimCnt; //�A�j���[�V�����J�E���g
	D3DXVECTOR2 m_tex_move; //tex�ړ���

};
#endif