//=============================================
//
//3DTemplate[objectX.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECTX_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECTX_H_
#include "main.h"
#include "object.h"

//2D�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:
	static const int MAX_TEX = 256; //�e�N�X�`���̐�

	CObjectX(int nPriority);
	~CObjectX()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Idx);

	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

	//scale�̑��
	inline void SetScale(D3DXVECTOR3 scale)
	{
		m_scale = scale;
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

	//�ŏ��l���
	inline void SetMinPos(D3DXVECTOR3 MinPos)
	{
		m_minpos = MinPos;
	}

	//�ő�l���
	inline void SetMaxPos(D3DXVECTOR3 MaxPos)
	{
		m_maxpos = MaxPos;
	}

	//���[���h�}�g���b�N�X�̑��
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//�J���[�̑��
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	//scale�̎擾
	inline D3DXVECTOR3& GetScale()
	{
		return m_scale;
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

	//TODO:���̏������ł�������inline�W�J�ł��Ȃ��\����
	//�ŏ��l�擾
	D3DXVECTOR3& GetMinPos();

	//�ő�l�擾
	D3DXVECTOR3& GetMaxPos();

	//���b�V�����擾
	inline LPD3DXMESH& GetpMesh()
	{
		return m_pMesh;
	}

	//�}�e���A�����擾
	inline LPD3DXBUFFER& GetpBuffMat()
	{
		return m_pBuffMat;
	}

	//�}�e���A�����擾
	inline DWORD& GetNumMat()
	{
		return m_dwNumMat;
	}

	//���[���h�}�g���b�N�X�擾
	inline D3DXMATRIX& GetMtxWorld() 
	{
		return m_mtxWorld;
	}

	//�J���[�擾
	inline D3DXCOLOR& GetCol()
	{
		return m_col;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX]; //�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_minpos; //pos�ŏ��l
	D3DXVECTOR3 m_maxpos; //pos�ő�l

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	
	LPD3DXMESH m_pMesh; //���b�V�����
	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	DWORD m_dwNumMat; //�}�e���A����

	D3DXCOLOR m_col; //�J���[�̒l
};
#endif