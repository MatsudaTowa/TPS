//=============================================
//
//�Q�[�W�Ǘ�[gauge.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"

//=============================================
//2D�Q�[�W�N���X
//=============================================
class CGauge_2D : public CObject2D
{
public:
	enum GAUGE2D_TYPE
	{
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_STAMINA,
		GAUGE_TYPE_MAX,
	};
	static const int GAUGE2D_PRIORITY = 28;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CGauge_2D(int nPriority = GAUGE2D_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CGauge_2D()override;
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
	 * @brief �Q�[�W�̐ݒ�
	 * @param [in]�Q�[�W�̃T�C�Y
	 */
	void SetGauge(D3DXVECTOR2 size);
	/**
	 * @brief �Q�[�W�̐���
	 * @param [in]�ʒu
	 * @param [in]�T�C�Y
	 * @param [in]�^�C�v
	 * @param [in]�F
	 * @return �Q�[�W�|�C���^
	 */
	static CGauge_2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	GAUGE2D_TYPE m_type;
};

//=============================================
//�̗̓Q�[�W�N���X
//=============================================
class CGauge_Life : public CGauge_2D
{
public:
	CGauge_Life(int nPriority = GAUGE2D_PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//=============================================
//�X�^�~�i�Q�[�W�N���X
//=============================================
class CGauge_Stamina : public CGauge_2D
{
public:
	CGauge_Stamina(int nPriority = GAUGE2D_PRIORITY);
	~CGauge_Stamina()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif