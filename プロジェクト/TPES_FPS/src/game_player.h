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
	CGamePlayer(int nPriority = PLAYER_PRIORITY);
	~CGamePlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif