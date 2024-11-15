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

	//pos�̑��
	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//rot�̑��
	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	//�T�C�Y�̑��
	void SetSize(D3DXVECTOR3 size)
	{
		m_size = size;
	}

	//�e�N�X�`�����W�̑��
	void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	//���[���h�}�g���b�N�X�̑��
	void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//���_���̑��
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff)
	{
		m_pVtxBuff = vtxBuff;
	}

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


	//���_���W�̑��
	void SetVtx(D3DXVECTOR3 nor, D3DCOLOR col);

	//���_���W�̑��
	void SetVtx(D3DXVECTOR3 nor,float fAngle, float fLength, D3DCOLOR col);

	//���_���W�̑��
	void SetVtxAnim(D3DXVECTOR3 nor, D3DCOLOR col, D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);
	void SetVtx_FootPos(D3DXVECTOR3 nor, D3DCOLOR col);

	//pos�̎擾
	D3DXVECTOR3& GetPos();

	//rot�̎擾
	D3DXVECTOR3& GetRot();

	//�T�C�Y�̎擾
	D3DXVECTOR3& GetSize();

	//�e�N�X�`�����W�̎擾
	D3DXVECTOR2& GetTexPos();

	//���_���擾
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();

	//�e�N�X�`�����擾
	LPDIRECT3DTEXTURE9& GetTexture();

	//���[���h�}�g���b�N�X�擾
	D3DXMATRIX& GetMtxWorld();

	//�A�j���[�V�����t���[���擾
	int GetAnimFrame();

	//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2& GetTexMove();

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

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