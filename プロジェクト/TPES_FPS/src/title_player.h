//=============================================
//
//�^�C�g���v���C���[[title_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_PLAYER_H_
#include "main.h"
#include "player.h"

//=============================================
//�^�C�g���v���C���[�N���X
//=============================================
class CTitlePlayer :public CPlayer
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CTitlePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTitlePlayer()override;
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