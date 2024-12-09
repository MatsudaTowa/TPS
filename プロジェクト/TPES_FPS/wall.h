//=============================================
//
//�ǂ̏���[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WALL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WALL_H_
#include "main.h"
#include "object3D.h"

//�����_���[�N���X
class CWall : public CObject3D
{
public:
	static const int WALL_PRIORITY = 3; //�`�揇

	CWall(int nPriority = WALL_PRIORITY);
	~CWall()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CWall* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif