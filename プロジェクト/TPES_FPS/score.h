//=============================================
//
//�X�R�A�����uscorer.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SCORE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CScore
{
public:
	static const int NUM_DIGIT = 6;  //����
	static const float DIGIT_SHIFT;  //�����Ƃɍ��W�����炷
	static const float DEBUG_DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	CScore();
	~CScore();
	HRESULT Init();
	void Uninit();
	void Update();
	void AddScore(int nValue);
	int m_nScore; //�X�R�A�̒l
	void SaveScore(int nScore)
	{
		m_nSaveScore = nScore;
	}
	static int GetScore();
private:
	void SetScore(int nScore);
	static int m_nSaveScore; //�X�R�A�Z�[�u�p
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG