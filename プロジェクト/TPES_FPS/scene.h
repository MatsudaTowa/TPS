//=============================================
//
//�V�[��[scene.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SCENE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SCENE_H_
#include "main.h"

//=============================================
// �V�[���N���X
//=============================================
class CScene
{
public:

	//��ʂ̎�ނ̗�
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TEST,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	};

	CScene();
	virtual ~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	static CScene* Create(MODE mode);
	static MODE GetSceneMode();
private:
	static MODE m_Mode; //���݂̃��[�h
};
#endif