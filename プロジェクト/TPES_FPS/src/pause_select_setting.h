//=============================================
//
//�|�[�Y��UI_�Z�b�e�B���O[pause_select_setting.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_SETTING_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PAUSE_SELECT_SETTING_H_
#include "main.h"
#include "pause_select.h"

//=============================================
//�|�[�Y�I��UI(setting)�N���X
//=============================================
class CPauseSelectSetting : public CPauseSelect
{
public:
	static const int PRIORITY = 21;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CPauseSelectSetting(int nPriority = PRIORITY);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CPauseSelectSetting()override;
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
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif