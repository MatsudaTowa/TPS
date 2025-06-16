//=============================================
//
//�A�N�V����UI�̕\�L[action_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTION_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ACTION_UI_H_
#include "main.h"
#include "object2D.h"

/**
* @brief �A�N�V����UI�N���X
* @copydoc CObject2D
*/
class CAction_UI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //�`�揇

	enum ACTION_TYPE
	{
		ACTION_MOVE = 0,
		ACTION_SHOTMODE,
		ACTION_SHOT,
		ACTION_RELOAD,
		ACTION_ULT,
		ACTION_SMOKE,
		ACTION_MAX
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CAction_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAction_UI()override;
	/**
	 * @brief �R���X�g���N�^
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
	 * @brief �R���X�g���N�^
	 * @param[in]�ʒu
	 * @param[in]�T�C�Y
	 * @param[in]�F
	 * @param[in]�ǂ̃^�C�v��
	 * @return �A�N�V������UI�|�C���^
	 */
	static CAction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ACTION_TYPE type);
private:
	static const std::string TEXTURE_NAME[ACTION_MAX];	//�e�N�X�`���̖��O
	ACTION_TYPE m_type;		//�A�N�V�����̃^�C�v
};
#endif