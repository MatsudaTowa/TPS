//=============================================
//
//�e�N�X�`���Ǘ�[texture.h]
//Auther Matsuda Towa
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
	CTexture();
	~CTexture();
	void Unload(); //�e�N�X�`���j��
	int Regist(const std::string*pTex);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX]; //�e�N�X�`���ւ̃|�C���^
	std::string* m_texName[MAX_TEX]; //�e�N�X�`���l�[���ۑ��p
	int m_nNumAll; //�e�N�X�`������
};
#endif