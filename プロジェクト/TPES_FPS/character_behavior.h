//=============================================
//
//キャラクターのストラテジーパターン[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //これが定義されてないとき

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

class CCharacter;

//=============================================
//移動ストラテジー
//=============================================
class CMove
{
public:
	CMove();
	virtual ~CMove();
	virtual void Move(float fSpeed, D3DXVECTOR3 vecDirection, float fRotMoveY,CCharacter*character, int motion) = 0;
protected:
};

class CDush : public CMove
{
public:
	CDush();
	~CDush() override;
	void Move(float fSpeed, D3DXVECTOR3 vecDirection, float fRotMoveY, CCharacter* character,int motion)override;
};


#endif
