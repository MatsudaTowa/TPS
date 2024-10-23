//=============================================
//
//�}�b�v�ɔz�u����I�u�W�F�N�gX[map_object.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAP_OBJECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MAP_OBJECT_H_
#include "main.h"
#include "objectX.h"

class CObjectMap : public CObjectX
{
public:
	static const std::string MESH_MODEL_NAME;	//���f���̖��O
	static const std::string WOOD_MODEL_NAME;	//���f���̖��O
	static const std::string AZUMAYA_MODEL_NAME;	//���f���̖��O
	static const std::string DANGOYA_MODEL_NAME;	//���f���̖��O

	static const int OBJECT_MAP_PRIORITY = 3; //�`�揇
	typedef enum
	{
		OBJECT_MAP_TYPE_NONE = 0,
		OBJECT_MAP_TYPE_MESH,
		OBJECT_MAP_TYPE_WOOD,
		OBJECT_MAP_TYPE_AZUMAYA,
		OBJECT_MAP_TYPE_DANGOYA,
		OBJECT_MAP_TYPE_MAX,
	}OBJECT_MAP_TYPE;

	CObjectMap(int nPriority = OBJECT_MAP_PRIORITY);
	~CObjectMap()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�}�b�v�I�u�W�F�N�g�쐬
	static CObjectMap* Create(OBJECT_MAP_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak);
private:
	OBJECT_MAP_TYPE m_type;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif