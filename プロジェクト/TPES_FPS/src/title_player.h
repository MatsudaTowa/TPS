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
	CTitlePlayer(int nPriority = PLAYER_PRIORITY);
	~CTitlePlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif