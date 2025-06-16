//=============================================
//
//�}�E�XUI�̕\�L[mouse_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�}�E�X�̕\�L�N���X
//=============================================
class CMouse_UI : public CObject2D
{
public:
	static const int PRIORITY = 27;  //�`�揇

	enum MOUSE_TYPE
	{
		MOUSE_R = 0,
		MOUSE_L,
		MOUSE_MAX
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMouse_UI(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMouse_UI()override;
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
	 * @param [in]�F
	 * @param [in]�^�C�v
	 * @return �}�E�X��UI�|�C���^
	 */
	static CMouse_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, MOUSE_TYPE type);
private:
	static const std::string TEXTURE_NAME[MOUSE_MAX];	//�e�N�X�`���̖��O
	MOUSE_TYPE m_type;
};
#endif