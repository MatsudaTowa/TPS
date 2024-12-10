//=============================================
//
//3DTemplate[object2D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT2D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//2D�I�u�W�F�N�g�N���X
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D()override;
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
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	//�e�N�X�`�����W�̑��
	void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
	{
		m_pVtxBuff = Buff;
	}

	//�F�̑��
	void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	//���_���W�̑��
	void SetVtx(float rhw);

	//���_���W(�g�k�A��])�̑��
	void SetVtx(float rhw,float fAngle,float fLength);

	void SetGaugeVtx(float rhw);

	void SetVtx_FootPos(float rhw,float fAngle,float fLength);

	//pos�̎擾
	D3DXVECTOR3& GetPos();

	//rot�̎擾
	D3DXVECTOR3& GetRot();

	//�T�C�Y�̎擾
	D3DXVECTOR2& GetSize();

	//�e�N�X�`�����W�̎擾
	D3DXVECTOR2& GetTexPos();
	
	//�F�̎擾
	D3DXCOLOR& GetColor();

	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_tex_pos; //tex���W
	D3DXCOLOR m_col;
};
#endif