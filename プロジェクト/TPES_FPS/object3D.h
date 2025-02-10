//=============================================
//
//3DTemplate[object3D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//=============================================
//3D�I�u�W�F�N�g�N���X
//=============================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	//�F�̎擾
	//�F�̑��
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	//pos�̑��
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//rot�̑��
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	//�T�C�Y�̑��
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_size = size;
	}

	//�e�N�X�`�����W�̑��
	inline void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	//���[���h�}�g���b�N�X�̑��
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//���_���̑��
	inline void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff)
	{
		m_pVtxBuff = vtxBuff;
	}

	//�A�j���[�V�����t���[�����
	inline void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	//�e�N�X�`���ړ��ʂ̑��
	inline void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}


	//���_���W�̑��
	void SetVtx(D3DXVECTOR3 nor);

	//���_���W�̑��
	void SetVtx(D3DXVECTOR3 nor,float fAngle, float fLength);

	//���_���W�̑��
	void SetVtxAnim(D3DXVECTOR3 nor,D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);
	void SetGaugeVtx(D3DXVECTOR3 ReferencePos,D3DXVECTOR3 nor);
	void SetVtx_FootPos(D3DXVECTOR3 nor);

	//�F�̎擾
	inline D3DXCOLOR& GetColor()
	{
		return m_col;
	}

	//pos�̎擾
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	//rot�̎擾
	inline D3DXVECTOR3& GetRot()
	{
		return m_rot;
	}

	//�T�C�Y�̎擾
	inline D3DXVECTOR3& GetSize()
	{
		return m_size;
	}

	//�e�N�X�`�����W�̎擾
	inline D3DXVECTOR2& GetTexPos()
	{
		return m_tex_pos;
	}

	//���_���擾
	inline LPDIRECT3DVERTEXBUFFER9& GetVtxBuff()
	{
		return m_pVtxBuff;
	}

	//�e�N�X�`�����擾
	inline LPDIRECT3DTEXTURE9& GetTexture()
	{
		return m_pTexture;
	}

	//���[���h�}�g���b�N�X�擾
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	//�A�j���[�V�����t���[���擾
	inline int GetAnimFrame()
	{
		return m_nAnimFrame;
	}

	//�e�N�X�`���ړ��ʎ擾
	inline D3DXVECTOR2& GetTexMove()
	{
		return m_tex_move;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	D3DXCOLOR m_col; //�F
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_size; //�T�C�Y
	D3DXVECTOR2 m_tex_pos; //tex���W

	//�A�j���[�V����
	int m_nAnimFrame; //�A�j���[�V�����t���[��
	int m_nAnimCnt; //�A�j���[�V�����J�E���g
	D3DXVECTOR2 m_tex_move; //tex�ړ���

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
};
#endif