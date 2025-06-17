//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

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
	* @brief �j���[�g��������
	* @param [in]�Q�[���v���C���[�|�C���^
	*/
	void Normal(CGame* game) override;
};

/** @brief ��ԏ����N���X */
class CPause :public CGameState
{
public:
	~CPause()override;
	/**
	* @brief �|�[�Y��ԏ���
	* @param [in]�Q�[���|�C���^
	*/
	void Pause(CGame* game) override;
private:
};

#endif // !_GAME_STATE_H_
