//=============================================
//
//3DTemplate[object.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT_H_
#include "main.h"

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	static const int MAX_OBJECT = 256; //�I�u�W�F�N�g�̍ő吔

	typedef enum
	{
		OBJECT_TYPE_NONE = 0,
		OBJECT_TYPE_TITLE,
		OBJECT_TYPE_TUTORIAL,
		OBJECT_TYPE_RESULT,
		OBJECT_TYPE_FADE,
		OBJECT_TYPE_NUMBER,
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_ENEMY,
		OBJECT_TYPE_BLOCK,
		OBJECT_TYPE_FIELD,
		OBJECT_TYPE_WALL,
		OBJECT_TYPE_EFFECT,
		OBJECT_TYPE_BG,
		OBJECT_TYPE_BULLET,
		OBJECT_TYPE_RETICLE,
		OBJECT_TYPE_MAX,
	}OBJECT_TYPE;

	CObject(int nPriority = MAX_PRIORITY);

	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void ReleaseAll(); //�S�I�u�W�F�N�g���

	static void UpdateAll(); //�S�I�u�W�F�N�g�X�V

	static void DrawAll(); //�S�I�u�W�F�N�g�`��

	static CObject* Getobject(int nPri,int nIdx);

	OBJECT_TYPE GetType();

	void SetType(OBJECT_TYPE type);

	OBJECT_TYPE m_type;
	
protected:
	void Release(); //�������g�̉��

private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];

	int m_nPriority; //�`��D��x

	static int m_nNumAll; //����

	int m_nID; //�I�u�W�F�N�g��ID
};
#endif