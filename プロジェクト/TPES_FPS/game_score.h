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
#include "death_icon.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CGameScore : public CScore
{
public:
	CGameScore();
	~CGameScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
	static const float DIGIT_SHIFT;
	static const int DEATH_DIGIT = 2;

	static const D3DXVECTOR3 BOX_POS; //�g�̈ʒu
	static const D3DXVECTOR2 BOX_SIZE; //�g�̃T�C�Y

	static const D3DXVECTOR3 DEATH_ICON_POS; //���S�A�C�R���̈ʒu
	static const D3DXVECTOR2 DEATH_ICON_SIZE; //���S�A�C�R���̃T�C�Y

	static const D3DXVECTOR3 NUM_DEATH_POS; //���S���̈ʒu
	static const D3DXVECTOR2 NUM_DEATH_SIZE; //���S���̃T�C�Y

	static const D3DXVECTOR3 SCORE_POS; //�X�R�A�̈ʒu
	static const D3DXVECTOR2 SCORE_SIZE; //�X�R�A�̃T�C�Y

	void SetDeathCntUI(int nDeathCnt);

	CNumber_2D* m_pDeathCnt[DEATH_DIGIT];
	CPlayerUIBox* m_pPlayerUIBox;
	CDeathIcon* m_pDeathIcon;

	D3DXVECTOR3 m_DeathCntPos;
};

#endif // DEBUG
