//=============================================
//
//���x�̐����usens_number.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SENS_NUMBER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SENS_NUMBER_H_
#include "main.h"
#include "number.h"

//=============================================
//�i���o�[�N���X2D
//=============================================
class CSensNumber :public CNumber_2D
{
public:
	static const int PRIORITY = 29;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CSensNumber(int nPriority = PRIORITY) :CNumber_2D(nPriority) {};
};
#endif // DEBUG