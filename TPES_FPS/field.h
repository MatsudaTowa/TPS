//=============================================
//
//3DTemplate[field.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//�����_���[�N���X
class CField : public CObject3D
{
public:

	static const int FIELD_PRIORITY = 3; //�`�揇

	CField(int nPriority = FIELD_PRIORITY);
	~CField()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CField* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif