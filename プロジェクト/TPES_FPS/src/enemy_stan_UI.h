//=============================================
//
//�G�̍�����UI[enemy_stan_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "enemy_reaction_UI.h"

#ifndef _ENEMY_STAN_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_STAN_UI_H_

class CEnemy_Stan_UI : public CEnemy_Reaction_UI
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CEnemy_Stan_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemy_Stan_UI()override;
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