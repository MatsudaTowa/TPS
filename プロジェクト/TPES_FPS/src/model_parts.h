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

	/**
	 * @brief �R���X�g���N�^
	 */
	CModel_Parts();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CModel_Parts();

	/**
	 * @brief ���f���j��
	 */
	void Unload();
	/**
	 * @brief ���f���ݒ�
	 * @param [in]�}�e���A���o�b�t�@
	 * @param [in]�}�e���A����
	 * @param [in]���b�V�����
	 */
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

	/**
	 * @brief �`��
	 */
	void Draw();
	/**
	 * @brief �`��
	 * @param [in]�F
	 */
	void Draw(D3DXCOLOR col);

	/**
	 * @brief ���[���h�}�g���b�N�X�ϊ�
	 */
	void ConversionMtxWorld();

	/**
	 * @brief �p�[�c����
	 * @param [in]�ʒu
	 * @param [in]����
	 * @param [in]���f���̃p�X
	 * @return ���f���p�[�c�|�C���^
	 */
	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,char* pModel_Path);

	/**
	 * @brief ���[���h�}�g���b�N�X�̑��
	 * @param [in]���[���h�}�g���b�N�X
	 */
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	/**
	 * @brief �ʒu�̑��
	 * @param [in]�ʒu
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	};

	/**
	 * @brief T�|�[�Y�̈ʒu���
	 * @param [in]T�|�[�Y�̈ʒu
	 */
	inline void SetTPos(D3DXVECTOR3 Tpos)
	{
		m_Tpos = Tpos;
	};

	/**
	 * @brief �ߋ��̈ʒu���
	 * @param [in]�ߋ��̈ʒu
	 */
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	};

	/**
	 * @brief �������
	 * @param [in]����
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	};

	/**
	 * @brief T�|�[�Y�������
	 * @param [in]����
	 */
	inline void SetTRot(D3DXVECTOR3 Trot)
	{
		m_Trot = Trot;
	};

	/**
	 * @brief �u���b�N�̔�������
	 * @param [in]�u���b�N�̔�����
	 */
	inline void SetColisionBlockInfo(ColisionBlockInfo ColisionBlockInfo)
	{
		m_ColisionBlockInfo = ColisionBlockInfo;
	}

	/**
	 * @brief �e���
	 * @param [in]�e���
	 */	
	inline void SetParent(CModel_Parts* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 * @brief �p�[�c�ԍ�
	 * @param [in]�ԍ�
	 */
	inline void SetIdx(int nIdx)
	{
		m_nIdx = nIdx;
	}

	/**
	 * @brief �e�ԍ����
	 * @param [in]�e�ԍ�
	 */
	inline void SetParentIdx(int nParent)
	{
		m_nIdxModelParent = nParent;
	}

	/**
	 * @brief �ʒu���擾
	 * @return �ʒu
	 */
	inline D3DXVECTOR3 GetPos()
	{
		return m_pos;
	};

	/**
	 * @brief T�|�[�Y�̈ʒu���擾
	 * @return T�|�[�Y�ʒu
	 */
	inline D3DXVECTOR3 GetTPos()
	{
		return m_Tpos;
	};

	/**
	 * @brief �ߋ��̈ʒu���擾
	 * @return �ߋ��̈ʒu
	 */
	inline D3DXVECTOR3 GetOldPos()
	{
		return m_oldpos;
	};

	/**
	 * @brief �������擾
	 * @return ����
	 */
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	};

	/**
	 * @brief T�|�[�Y�̕����擾
	 * @return T�|�[�Y�̕���
	 */
	inline D3DXVECTOR3 GetTRot()
	{
		return m_Trot;
	};

	/**
	 * @brief �ŏ��ʒu�擾
	 * @return �ŏ��ʒu
	 */
	inline D3DXVECTOR3 GetMin()
	{
		return m_minpos;
	}

	/**
	 * @brief �ő�ʒu�擾
	 * @return �ő�ʒu
	 */
	inline D3DXVECTOR3 GetMax()
	{
		return m_maxpos;
	}

	/**
	 * @brief ���f���ԍ��擾
	 * @return ���f���ԍ�
	 */
	inline int GetIdx()
	{
		return m_nIdx;
	}

	/**
	 * @brief ���f���̐e�ԍ��擾
	 * @return ���f���̐e�ԍ�
	 */
	inline int GetParentIdx()
	{
		return m_nIdxModelParent;
	}

	/**
	 * @brief �u���b�N�̔�����擾
	 * @return �u���b�N�̔�����
	 */
	inline ColisionBlockInfo& GetColisionBlockInfo()
	{
		return m_ColisionBlockInfo;
	}

	/**
	 * @brief ���[���h�}�g���b�N�X�擾
	 * @return ���[���h�}�g���b�N�X
	 */
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	/**
	 * @brief ���f�����擾
	 * @param [in]�ԍ�
	 * @return ���f�����
	 */
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