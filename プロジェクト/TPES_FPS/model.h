//=============================================
//
//3DTemplate[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MODEL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MODEL_H_
#include "main.h"

class CModel
{
public:
	static const int MAX_MODEL = 256; //���f���̐�

	//���f�����\���̒�`
	typedef struct
	{
		LPD3DXMESH pMesh; //���b�V�����
		LPD3DXBUFFER pBuffMat; //�}�e���A�����
		DWORD dwNumMat; //�}�e���A����;
		std::string* ModelName; //���f���l�[���ۑ��p
	}MODEL_INFO;

	CModel();
	~CModel();
	void Unload(); //���f���j��
	int Regist(const std::string* pModel);
	int Regist(const char* pModel);
	MODEL_INFO GetModelInfo(int nIdx); //���f�����擾

private:
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //���f�����
	int m_nNumAll; //���f������
};
#endif