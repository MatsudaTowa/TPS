//=============================================
//
//�`���[�g���A���v���C���[[tutorial_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TUTORIAL_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//�`���[�g���A���v���C���[�N���X
//=============================================
class CTutorialPlayer :public CActivePlayer
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CTutorialPlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTutorialPlayer()override;
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