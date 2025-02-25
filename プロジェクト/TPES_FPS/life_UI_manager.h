//=============================================
//
//�̗͕\���ulife_UI_manager.h�v
// Author���c�i�v
//
//=============================================
#ifndef _LIFE_UI_MANAGER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _LIFE_UI_MANAGER_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"
#include "gauge.h"

//=============================================
//�̗͕\���N���X
//=============================================
class CLife_UI_Manager
{
public:
	static const int NUM_DIGIT = 3;  //����
	static constexpr float DIGIT_SHIFT = 18.0f;  //�����Ƃɍ��W�����炷

	CLife_UI_Manager();
	~CLife_UI_Manager();
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