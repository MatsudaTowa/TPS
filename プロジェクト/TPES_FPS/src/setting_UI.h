//=============================================
//
//�ݒ��UI�usetting_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SETTING_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SETTING_UI_H_
#include "main.h"
#include "object2D.h"
#include "sens_number.h"
#include "gauge.h"
#include "pause_mask.h"
#include "decimal_point.h"
#include "sens_txt_UI.h"

//=============================================
//�ݒ�UI�N���X
//=============================================
class CSetting_UI
{
public:
	static const int NUM_DIGIT = 3;  //����
	static constexpr float DIGIT_SHIFT = 33.0f;  //�����Ƃɍ��W�����炷
	/**
	 * @brief �R���X�g���N�^
	 */
	CSetting_UI();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSetting_UI();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();

	/**
	 * @brief ���xUI�ݒ�
	 * @param [in]���x
	 */
	void SetSens_UI(float sens);

	/**
	 * @brief ���x�̐����ݒ�
	 * @param [in]���x
	 */
	void SetNumber(float sens);

private:
	static const D3DXVECTOR3 GAUGE_POS; //�Q�[�W�̈ʒu
	static const D3DXVECTOR2 GAUGE_SIZE; //�Q�[�W�̃T�C�Y

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y

	static const D3DXVECTOR3 DECIMAL_POINT_POS; //�����_�̈ʒu
	static const D3DXVECTOR2 DECIMAL_POINT__SIZE; //�����_�̃T�C�Y

	static const D3DXVECTOR3 TXT_POS;	//�����̈ʒu
	static const D3DXVECTOR2 TXT_SIZE;	//�����̃T�C�Y
	CMask* m_pMask;
	CDecimalPoint* m_pDecimalPoint;
	CNumber_2D* m_pNumber[NUM_DIGIT];
	CGauge_2D* m_pGauge;
	CSensTxtUI* m_pTxtUI;
	D3DXVECTOR3 m_NumPos;
};

#endif // DEBUG