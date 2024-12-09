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

	CScore();
	virtual ~CScore();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	void AddScore(int nValue);
	void ExportScore(const std::string* pFileName); //�X�R�A�����o��
	void Reset();

	int m_nScore; //�X�R�A�̒l
	void SetScore(int nScore);

	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	D3DXVECTOR3& GetPos();
	float& GetDigitShift();
	CNumber_2D* m_pNumber[NUM_DIGIT];
private:
	D3DXVECTOR3 m_pos;
	float m_DigitShift;
};

#endif // DEBUG