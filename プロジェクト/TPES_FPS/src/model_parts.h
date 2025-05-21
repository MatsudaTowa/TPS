//=============================================
// 
//�e�q�֌W�̃p�[�c[model.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MODEL_PARTS_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MODEL_PARTS_H_
#include "main.h"
#include "objectX.h"
#include "block.h"

//=============================================
// ���f���p�[�c�N���X
//=============================================
class CModel_Parts
{
public:
	static const int MAX_MODEL = 256; //���f���̐�

	//���f�����\���̒�`
	struct MODEL_INFO
	{
		LPD3DXMESH pMesh; //���b�V�����
		LPD3DXBUFFER pBuffMat; //�}�e���A�����
		DWORD dwNumMat; //�}�e���A����;
		char* ModelName; //���f���l�[���ۑ��p
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X���ɓ������Ă���
		bool bColision_Y; //Y���ɓ������Ă���
		bool bColision_Z; //Z���ɓ������Ă���

		float Radius;
		CBlock* pBlock;
	};

	CModel_Parts();
	~CModel_Parts();
	void Unload(); //���f���j��
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);
	void Draw();
	void Draw(D3DXCOLOR col);

	void ConversionMtxWorld();

	//�p�[�c����
	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,char* pModel_Path);

	//���[���h�}�g���b�N�X�̑��
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//�ʒu���
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	};

	//T�|�[�Y���̈ʒu���
	inline void SetTPos(D3DXVECTOR3 Tpos)
	{
		m_Tpos = Tpos;
	};

	//�ߋ��̈ʒu���
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	};

	//�������
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	};

	//T�|�[�Y���̕������
	inline void SetTRot(D3DXVECTOR3 Trot)
	{
		m_Trot = Trot;
	};

	//���������u���b�N�����
	inline void SetColisionBlockInfo(ColisionBlockInfo ColisionBlockInfo)
	{
		m_ColisionBlockInfo = ColisionBlockInfo;
	}

	//�e�p�[�c�̐ݒ�
	inline void SetParent(CModel_Parts* pParent)
	{
		m_pParent = pParent;
	}

	//���f���̔ԍ��ݒ�
	inline void SetIdx(int nIdx)
	{
		m_nIdx = nIdx;
	}

	//�e�ԍ��̐ݒ�
	inline void SetParentIdx(int nParent)
	{
		m_nIdxModelParent = nParent;
	}

	//�ʒu�擾
	inline D3DXVECTOR3 GetPos()
	{
		return m_pos;
	};

	//T�|�[�Y���̈ʒu�擾
	inline D3DXVECTOR3 GetTPos()
	{
		return m_Tpos;
	};

	//�ߋ��̈ʒu�擾
	inline D3DXVECTOR3 GetOldPos()
	{
		return m_oldpos;
	};

	//�����擾
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	};

	//T�|�[�Y���̕����擾
	inline D3DXVECTOR3 GetTRot()
	{
		return m_Trot;
	};

	//�ŏ��l�擾
	inline D3DXVECTOR3 GetMin()
	{
		return m_minpos;
	}

	//�ő�l�擾
	inline D3DXVECTOR3 GetMax()
	{
		return m_maxpos;
	}

	//���f���̔ԍ��擾
	inline int GetIdx()
	{
		return m_nIdx;
	}

	//���f���̐e�ԍ��擾
	inline int GetParentIdx()
	{
		return m_nIdxModelParent;
	}

	//���������u���b�N���擾
	inline ColisionBlockInfo& GetColisionBlockInfo()
	{
		return m_ColisionBlockInfo;
	}

	//���[���h�}�g���b�N�X�擾
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	//���f�����擾
	inline MODEL_INFO GetModelInfo(int nIdx)
	{
		return m_ModelInfo[nIdx];
	}

private:
	LPDIRECT3DTEXTURE9 m_pTexture[256]; //�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //���f�����

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Tpos;
	D3DXVECTOR3 m_Trot;
	int m_nIdx; //���Ԗڂ̃p�[�c��
	int m_nIdxModelParent; //�e�̃C���f�b�N�X

	D3DXVECTOR3 m_minpos; //pos�ŏ��l
	D3DXVECTOR3 m_maxpos; //pos�ő�l
	D3DXVECTOR3 m_oldpos;
	int m_nNumAll; //���f������

	CModel_Parts*m_pParent; //�e�p�[�c�ւ̃|�C���^
	ColisionBlockInfo m_ColisionBlockInfo; //����������

};
#endif