//=============================================
// 
//�e�q�֌W�̃p�[�c[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MODEL_PARTS_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MODEL_PARTS_H_
#include "main.h"
#include "objectX.h"

class CModel_Parts
{
public:
	static const int MAX_MODEL = 256; //���f���̐�

	//���f�����\���̒�`
	typedef struct
	{
		LPD3DXMESH pMesh; //���b�V�����
		LPD3DXBUFFER pBuffMat; //�}�e���A�����
		DWORD dwNumMat; //�}�e���A����;
		char* ModelName; //���f���l�[���ۑ��p
	}MODEL_INFO;

	CModel_Parts();
	~CModel_Parts();
	void Unload(); //���f���j��
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);
	void Draw();
	void Draw(D3DXCOLOR col);

	//�p�[�c����
	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,char* pModel_Path);

	//���[���h�}�g���b�N�X�̑��
	void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	};

	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	};

	D3DXVECTOR3 GetPos()
	{
		return m_pos;
	};

	D3DXVECTOR3 GetRot()
	{
		return m_rot;
	};
	void SetParent(CModel_Parts*pParent);


	//���[���h�}�g���b�N�X�擾
	D3DXMATRIX& GetMtxWorld();

	MODEL_INFO GetModelInfo(int nIdx); //���f�����擾

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Tpos;
	D3DXVECTOR3 m_Trot;
	D3DXVECTOR3 m_minpos; //pos�ŏ��l
	D3DXVECTOR3 m_maxpos; //pos�ő�l
	int m_nIdx; //���Ԗڂ̃p�[�c��
	char PARTS_NAME[256];
	int m_nIdxModelParent; //�e�̃C���f�b�N�X
private:
	LPDIRECT3DTEXTURE9 m_pTexture[256]; //�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //���f�����

	int m_nNumAll; //���f������

	CModel_Parts*m_pParent; //�e�p�[�c�ւ̃|�C���^
};
#endif