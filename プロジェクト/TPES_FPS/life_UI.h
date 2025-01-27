//=============================================
//
//�̗͕\���ulife_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _LIFE_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _LIFE_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"
#include "gauge.h"

//=============================================
//�̗͕\���N���X
//=============================================
class CLife_UI
{
public:
	static const int NUM_DIGIT = 3;  //����
	static const float DIGIT_SHIFT;  //�����Ƃɍ��W�����炷

	CLife_UI();
	~CLife_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nLife; //�̗͂̒l
	void SetLife_UI(int nLife);

	void SetNumber(int nLife);

private:
	static const D3DXVECTOR3 BOX_POS; //�g�̈ʒu
	static const D3DXVECTOR2 BOX_SIZE; //�g�̃T�C�Y

	static const D3DXVECTOR3 GAUGE_POS; //�Q�[�W�̈ʒu
	static const D3DXVECTOR2 GAUGE_SIZE; //�Q�[�W�̃T�C�Y

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y
	CNumber_2D* m_pNumber[NUM_DIGIT];
	CPlayerUIBox* m_pUIBox;
	CGauge_2D*m_pGauge;
	D3DXVECTOR3 m_NumPos;
};

#endif // DEBUG