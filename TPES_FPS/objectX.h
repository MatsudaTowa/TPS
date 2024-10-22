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
	static const int MAX_TEX = 16; //�e�N�X�`���̐�

	CObjectX(int nPriority = 3);
	~CObjectX()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Draw(D3DXCOLOR col);

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

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

	//�ŏ��l���
	void SetMinPos(D3DXVECTOR3 MinPos)
	{
		m_minpos = MinPos;
	}

	//�ő�l���
	void SetMaxPos(D3DXVECTOR3 MaxPos)
	{
		m_maxpos = MaxPos;
	}

	//���[���h�}�g���b�N�X�̑��
	void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//�J���[�̑��
	void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	//pos�̎擾
	D3DXVECTOR3& GetPos();

	//rot�̎擾
	D3DXVECTOR3& GetRot();

	//�ŏ��l�擾
	D3DXVECTOR3& GetMinPos();

	//�ő�l�擾
	D3DXVECTOR3& GetMaxPos();

	//���b�V�����擾
	LPD3DXMESH& GetpMesh();

	//�}�e���A�����擾
	LPD3DXBUFFER& GetpBuffMat();

	//�}�e���A�����擾
	DWORD& GetNumMat();

	//���[���h�}�g���b�N�X�擾
	D3DXMATRIX& GetMtxWorld();

	//�J���[�擾
	D3DXCOLOR& GetCol();

private:

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX]; //�e�N�X�`���ւ̃|�C���^

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