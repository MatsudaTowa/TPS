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

private:
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG