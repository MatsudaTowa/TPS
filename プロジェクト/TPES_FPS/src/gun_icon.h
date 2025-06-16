//=============================================
//
//�e�̕\�L[gun_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GUN_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GUN_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�e�̕\�L�N���X
//=============================================
class CGunIcon : public CObject2D
{
public:
	static const int GUN_ICON_PRIORITY = 25;  //�`�揇

	enum ICON_TYPE
	{
		ICON_TYPE_AR,
		ICON_TYPE_MAX,
	};
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CGunIcon(int nPriority = GUN_ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CGunIcon()override;
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
	 * @return �e�̃A�C�R��
	 */
	static CGunIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ICON_TYPE type);
private:
};

//=============================================
//�A�T���g�̃A�C�R��
//=============================================
class CARIcon : public CGunIcon
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CARIcon(int nPriority = GUN_ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CARIcon()override;
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