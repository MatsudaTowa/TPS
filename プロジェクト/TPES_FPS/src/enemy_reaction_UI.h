//=============================================
//
//�G�̃��A�N�V������UI[enemy_reaction_UI.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _ENEMY_REACTION_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_REACTION_UI_H_

//=============================================
// �G�l�~�[�̃��A�N�V����UI�N���X
//=============================================
class CEnemy_Reaction_UI : public CBillboard
{
public:
	static const int PRIORITY = 17; //�`�揇

	enum REACTION
	{
		REACTION_RELOAD = 0,
		REACTION_CONFUSION,
		REACTION_STAN,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CEnemy_Reaction_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CEnemy_Reaction_UI()override;
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
	 * @param [in]�T�C�Y
	 * @param [in]�^�C�v
	 * @return ���A�N�V����UI�|�C���^
	 */
	static CEnemy_Reaction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, REACTION type);

private:
};

#endif