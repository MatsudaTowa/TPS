//=============================================
//
//�E�F�[�u���U���g���[wave_result_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_RESULT_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�E�F�[�u���U���g
//=============================================
class CWave_Result_Screen : public CObject2D
{
public:
	static const int RESULT_SCREEN_PRIORITY = 15;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CWave_Result_Screen(int nPriority = RESULT_SCREEN_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CWave_Result_Screen()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
	/**
	 * @brief ����
	 * @param [in]�ʒu
	 * @return �E�F�[�uUI�|�C���^
	 */
	static CWave_Result_Screen* Create(D3DXVECTOR3 pos);
private:
	static const D3DXCOLOR COLOR;
};
#endif