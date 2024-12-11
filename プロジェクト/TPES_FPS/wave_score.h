//=============================================
//
//�E�F�[�u�X�R�A�����uwave_scorer.h�v
// Author���c�i�v
//
//=============================================
#ifndef _WAVE_SCORE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _WAVE_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CWaveScore : public CScore
{
public:
	static const float DIGIT_SHIFT;
	CWaveScore();
	~CWaveScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y
};

#endif // DEBUG
