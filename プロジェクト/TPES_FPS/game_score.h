//=============================================
//
//�Q�[���X�R�A�����ugame_scorer.h�v
// Author���c�i�v
//
//=============================================
#ifndef _GAME_SCORE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _GAME_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CGameScore : public CScore
{
public:
	static const float DIGIT_SHIFT;
	CGameScore();
	~CGameScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
};

#endif // DEBUG
