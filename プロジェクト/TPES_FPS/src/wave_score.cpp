//=============================================
//
//�E�F�[�u�X�R�A�����uwave_scorer.h�v
// Author���c�i�v
//
//=============================================
#include "wave_score.h"

//�����̕\���ʒu
const D3DXVECTOR3 CWaveScore::NUM_POS = { 850.0f ,SCREEN_HEIGHT * 0.5f,0.0f };
//�����̕\���T�C�Y
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
	CScore::SetPos(NUM_POS);	//�ʒu�ݒ�
	CScore::SetSize(NUM_SIZE);	//�T�C�Y�ݒ�
	CScore::SetDigitShift(DIGIT_SHIFT);	//�����炵���W
	CScore::Init();	//������
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CWaveScore::Uninit()
{
	//�I��
	CScore::Uninit();
}

//=============================================
//�X�V
//=============================================
void CWaveScore::Update()
{
	//�X�V
	CScore::Update();
}
