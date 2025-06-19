//=============================================
//
//�A�N�e�B�u�V�[���̃X�e�[�g�p�^�[��[active_scene_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_SCENE_STATE_H_
#define _ACTIVE_SCENE_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"
#include "pause_select_continue.h"
#include "pause_select_retry.h"
#include "pause_select_quit.h"

//=============================================
//�O���錾
//=============================================
class CActiveScene;

/** @brief �A�N�e�B�u�V�[���̃X�e�[�g�N���X */
class CActiveSceneState
{
public:
	CActiveSceneState() {};
	virtual ~CActiveSceneState() {};
	/**
	* @brief �ʏ폈��(�e�ł͉������Ȃ�)
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	virtual void Normal(CActiveScene* active_scene) {};

	/**
	* @brief �|�[�Y��ԏ���(�e�ł͉������Ȃ�)
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	virtual void Pause(CActiveScene* active_scene) {};
};

/** @brief �ʏ�N���X */
class CNormal :public CActiveSceneState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CNormal();
	/**
	* @brief �j���[�g��������
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	void Normal(CActiveScene* active_scene) override;
};

/** @brief ��ԏ����N���X */
class CPause :public CActiveSceneState
{
public:
	enum PAUSE_SELECT
	{
		CONTINUE = 0,
		RETRY,
		QUIT,
		MAX
	};
	/**
	 * @brief �R���X�g���N�^
	 */
	CPause();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPause()override;
	/**
	* @brief �|�[�Y��ԏ���
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	void Pause(CActiveScene* active_scene) override;
	/**
	 * @brief �|�[�Y�̑I�����ꂽUI�̍X�V���s����
	 * @param [in]�A�N�e�B�u�V�[���̃|�C���^
	 */
	virtual void HandlePoseSelection(CActiveScene* active_scene) {};

	/**
	 * @brief �|�[�Y�L�����Z��
	 * @param [in]�A�N�e�B�u�V�[���̃|�C���^
	 */
	virtual void CancelPause(CActiveScene* active_scene) {};

	/**
	 * @brief �ǂ��I�����Ă邩�擾
	 * @return �I������Ă����
	 */
	inline int GetSelect()
	{
		return m_nSelect;
	}

	/**
	 * @brief �Z���N�g����Ă�UI
	 * @param [in]idx
	 * @return �I��UI
	 */
	inline CPauseSelect* GetSelectUI(int idx)
	{
		return m_pSelect[idx];
	}
private:
	static const D3DXVECTOR3 POS[MAX];

	int m_nSelect;
	CMask* m_pMask;
	CPauseSelect* m_pSelect[MAX];
};

#endif // !_GAME_STATE_H_
