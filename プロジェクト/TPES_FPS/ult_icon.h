//=============================================
//
//�E���g�̃}�[�N�̕\�L[ult_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ULT_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_ICON_H_
#include "main.h"
#include "object2D.h"

//�E���g�\�L�N���X
class CUltIcon : public CObject2D
{
public:
	static const int ULT_ICON_PRIORITY = 50;  //�`�揇
	static const D3DXCOLOR START_COLOR;
	enum ULT_TYPE
	{
		ULT_TYPE_MEDIUM,
		ULT_TYPE_MAX,
	};
	CUltIcon(int nPriority = ULT_ICON_PRIORITY);
	~CUltIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CUltIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type);
private:
	float m_AddColor; //�F���Z�̒l
};

class CMediumIcon : public CUltIcon
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	CMediumIcon(int nPriority = ULT_ICON_PRIORITY);
	~CMediumIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif