//=============================================
//
//�Q�[���v���C���[[game_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//�`���[�g���A���v���C���[�N���X
//=============================================
class CGamePlayer :public CActivePlayer
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CGamePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CGamePlayer()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
private:
};
#endif