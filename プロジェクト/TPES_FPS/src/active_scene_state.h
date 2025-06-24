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
#include "setting_UI.h"
#include "close_pause_UI.h"
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

	/**
	* @brief �ݒ��ԏ���(�e�ł͉������Ȃ�)
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	virtual void Setting(CActiveScene* active_scene) {};
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
		SETTING,
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
	virtual void HandlePoseSelection(CActiveScene* active_scene);

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
	static const D3DXVECTOR3 SELECT_POS[MAX];
	static const D3DXVECTOR3 CLOSE_POS;
	static const D3DXVECTOR2 CLOSE_SIZE;
	int m_nSelect;
	CMask* m_pMask;
	CClosePauseUI* m_pClosePause;
	CPauseSelect* m_pSelect[MAX];
};

/** @brief �ݒ�N���X */
class CSetting :public CActiveSceneState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CSetting();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSetting() override;
	/**
	* @brief �ݒ菈��
	* @param [in]�A�N�e�B�u�V�[���|�C���^
	*/
	void Setting(CActiveScene* active_scene) override;
private:
	/**
	 * @brief ���x�ύX
	 * @param [in][out]���x
	 */
	void ChangeSens(float& sens);

	static const int PRESS_FRAME = 5;	//���̃t���[�����L�[�������ꂽ�琔�l��i�߂�
	static constexpr float MIN_SENS = 0.011f;	//�ŏ����x
	static constexpr float MAX_SENS = 1.00f;	//�ő労�x
	static constexpr float CHANGE_SENS = 0.01f;	//���x�̕ϓ��l

	static const D3DXVECTOR3 CLOSE_POS;
	static const D3DXVECTOR2 CLOSE_SIZE;
	CSetting_UI* m_pSettingUI;	//�ݒ�UI
	CClosePauseUI* m_pClosePause;
	int m_nPressCnt;	//�L�[�̃v���X�J�E���g
};

#endif // !_GAME_STATE_H_
