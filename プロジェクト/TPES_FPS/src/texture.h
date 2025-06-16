//=============================================
//
//�e�N�X�`���Ǘ�[texture.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TEXTURE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TEXTURE_H_
#include "main.h"

//=============================================
// �e�N�X�`���Ǘ��N���X
//=============================================
class CTexture
{
public:
	static const int MAX_TEX = 256; //�e�N�X�`���̐�
	/**
	 * @brief �R���X�g���N�^
	 */
	CTexture();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTexture();
	/**
	 * @brief �e�N�X�`���j��
	 */
	void Unload();
	/**
	 * @brief �o�^
	 * @param [in]�e�N�X�`���p�X
	 * @return �e�N�X�`���o�^�ԍ�
	 */
	int Regist(const std::string*pTex);
	/**
	 * @brief �A�h���X�擾
	 * @param [in]�ԍ�
	 * @return �e�N�X�`���A�h���X
	 */
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX]; //�e�N�X�`���ւ̃|�C���^
	std::string* m_texName[MAX_TEX]; //�e�N�X�`���l�[���ۑ��p
	int m_nNumAll; //�e�N�X�`������
};
#endif