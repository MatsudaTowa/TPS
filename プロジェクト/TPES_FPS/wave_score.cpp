//=============================================
//
//�E�F�[�u�X�R�A�����uwave_scorer.h�v
// Author���c�i�v
//
//=============================================
#include "wave_score.h"

const float CWaveScore::DIGIT_SHIFT = 70.0f;

const D3DXVECTOR3 CWaveScore::NUM_POS = { 850.0f ,SCREEN_HEIGHT * 0.5f,0.0f };
const D3DXVECTOR2 CWaveScore::NUM_SIZE = { 40.0f, 50.0f };
//=============================================
//�R���X�g���N�^
//=============================================
CWaveScore::CWaveScore()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CWaveScore::~CWaveScore()
{
}

//=============================================
//������
//=============================================
HRESULT CWaveScore::Init()
{
	CScore::SetPos(NUM_POS);
	CScore::SetSize(NUM_SIZE);
	CScore::SetDigitShift(DIGIT_SHIFT);
	CScore::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWaveScore::Uninit()
{
	CScore::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWaveScore::Update()
{
	CScore::Update();
}
