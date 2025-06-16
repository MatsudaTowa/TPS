//=============================================
//
//�V�[��[scene.h]
//Author Matsuda Towa
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

	/**
	 * @brief �R���X�g���N�^
	 */
	CScene();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CScene();

	/**
	 * @brief ������
	 * @return ����������
	 */
	virtual HRESULT Init();
	/**
	 * @brief �I��
	 */
	virtual void Uninit();
	/**
	 * @brief �X�V
	 */
	virtual void Update();
	/**
	 * @brief �`��
	 */
	virtual void Draw();
	/**
	 * @brief ����
	 * @param [in]�V�[�����[�h
	 * @return �V�[���|�C���^
	 */
	static CScene* Create(MODE mode);
	/**
	 * @brief �V�[�����[�h�擾
	 * @return �V�[�����[�h
	 */
	static MODE GetSceneMode();
private:
	static MODE m_Mode; //���݂̃��[�h
};
#endif