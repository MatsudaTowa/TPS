//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"

//=============================================
//�O���錾
//=============================================
class CGame;

/** @brief �Q�[���̃X�e�[�g�N���X */
class CGameState
{
public:
	CGameState() {};
	virtual ~CGameState() {};
	/**
	* @brief �ʏ폈��(�e�ł͉������Ȃ�)
	* @param [in]�Q�[���|�C���^
	*/
	virtual void Normal(CGame* game) {};

	/**
	* @brief �|�[�Y��ԏ���(�e�ł͉������Ȃ�)
	* @param [in]�Q�[���|�C���^
	*/
	virtual void Pause(CGame* game) {};
};

/** @brief �ʏ�N���X */
class CNormal :public CGameState
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CNormal();
	/**
	* @brief �j���[�g��������
	* @param [in]�Q�[���v���C���[�|�C���^
	*/
	void Normal(CGame* game) override;
};

/** @brief ��ԏ����N���X */
class CPause :public CGameState
{
public:
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
	* @param [in]�Q�[���|�C���^
	*/
	void Pause(CGame* game) override;
	/**
	 * @brief �|�[�Y�̑I�����ꂽUI�̍X�V���s����
	 * @param [in]�Q�[���V�[���̃|�C���^
	 */
	void HandlePoseSelection(CGame* game);
private:
	enum PAUSE_SELECT
	{
		CONTINUE = 0,
		RETRY,
		QUIT,
		MAX
	};
	static const D3DXVECTOR3 POS[MAX];

	int m_nSelect;
	CMask* m_pMask;
	CPauseSelect* m_pSelect[MAX];
};

#endif // !_GAME_STATE_H_
