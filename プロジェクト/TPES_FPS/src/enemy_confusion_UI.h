//=============================================
//
//�G�̍�����UI[enemy_confusion_UI.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "enemy_reaction_UI.h"

#ifndef _ENEMY_WANDERING_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_WANDERING_UI_H_

//=============================================
//������Ԃ�UI�N���X
//=============================================
class CEnemy_Confusion_UI : public CEnemy_Reaction_UI
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CEnemy_Confusion_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemy_Confusion_UI()override;
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