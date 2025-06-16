//=============================================
//
//���f���Ǘ�[model.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MODEL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MODEL_H_
#include "main.h"

//=============================================
// ���f���Ǘ��N���X
//=============================================
class CModel
{
public:
	static const int MAX_MODEL = 256; //���f���̐�

	//���f�����\���̒�`
	struct MODEL_INFO
	{
		LPD3DXMESH pMesh; //���b�V�����
		LPD3DXBUFFER pBuffMat; //�}�e���A�����
		DWORD dwNumMat; //�}�e���A����;
		const char* ModelName; //���f���l�[���ۑ��p
	};

	/**
	 * @brief �R���X�g���N�^
	 */
	CModel();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CModel();
	/**
	 * @brief �A�����[�h
	 */
	void Unload();
	/**
	 * @brief �o�^
	 * @param [in]���f���̃p�X
	 * @return �o�^�ԍ�
	 */
	int Regist(const char* pModel);

	/**
	 * @brief ���f�����擾
	 * @param [in]�ԍ�
	 * @return ���f�����
	 */
	MODEL_INFO GetModelInfo(int nIdx);

private:
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //���f�����
	int m_nNumAll; //���f������
};
#endif