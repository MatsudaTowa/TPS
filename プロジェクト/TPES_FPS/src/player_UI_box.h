//=============================================
//
//�v���C���[��UI�̘g[player_UI_box.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�v���C���[��UI�̘g�N���X
//=============================================
class CPlayerUIBox : public CObject2D
{
public:
	static const int UI_BOX_PRIORITY = 20;  //�`�揇

	enum BOX_TYPE
	{
		BOX_TYPE_LIFE,
		BOX_TYPE_AMMO,
		BOX_TYPE_SCORE,
		BOX_TYPE_MAX,
	};
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPlayerUIBox()override;
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
	 * @return �v���C���[��UI�̘g
	 */
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col, BOX_TYPE type);
private:
};

//=============================================
//�v���C���[��UI�̗̘̑͂g�N���X
//=============================================
class CLifeUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CLifeUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CLifeUIBox()override;
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

//=============================================
//�v���C���[��UI�̎c�e�̘g�N���X
//=============================================
class CAmmoUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CAmmoUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CAmmoUIBox()override;
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

//=============================================
//�v���C���[��UI�̃X�R�A�̘g�N���X
//=============================================
class CScoreUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CScoreUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CScoreUIBox()override;
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