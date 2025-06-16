//=============================================
//
//3DTemplate[light.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _LIGHT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _LIGHT_H_
#include "main.h"
#include "input.h"

class CLight
{
public:
	static const int MAX_LIGHT = 3; //���C�g�ő吔
	/**
	 * @brief �R���X�g���N�^
	 */
	CLight();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CLight();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT]; //���C�g���

};
#endif