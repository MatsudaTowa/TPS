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
#include "player_UI_box.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CScore
{
public:
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

	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	D3DXVECTOR3& GetPos();
	D3DXVECTOR2& GetSize();
	float& GetDigitShift();
private:
	static const int NUM_DIGIT = 6;  //����

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
	CNumber_2D* m_pNumber[NUM_DIGIT];

	float m_DigitShift;
};
#endif // DEBUG