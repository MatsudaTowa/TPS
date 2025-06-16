//=============================================
//
//�E���g�̃}�[�N�̕\�L[ult_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ULT_ICON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_ICON_H_
#include "main.h"
#include "object2D.h"
#include "ult_icon_effect.h"

//=============================================
//�E���g�\�L�N���X
//=============================================
class CUltIcon : public CObject2D
{
public:
	static const int ULT_ICON_PRIORITY = 21;  //�`�揇
	static const D3DXCOLOR START_COLOR;
	enum ULT_TYPE
	{
		ULT_TYPE_MEDIUM,
		ULT_TYPE_MAX,
	};
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CUltIcon(int nPriority = ULT_ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUltIcon()override;
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
	 * @param [in]���Z�l
	 * @param [in]�^�C�v
	 * @return �E���g��UI�|�C���^
	 */
	static CUltIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type);

	/**
	 * @brief ���Z�b�g
	 */
	void Reset();
private:
	static const D3DXVECTOR2 EFFECT_SIZE;
	static const D3DXCOLOR EFFECT_COLOR;
	bool m_isAddColor; //�E���g�����܂�����false��
	float m_AddColor; //�F���Z�̒l
	CUltIconEffect* m_pIconEffect;
};

//=============================================
//�ʏ�L�����̃E���g�̃A�C�R���N���X
//=============================================
class CMediumIcon : public CUltIcon
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMediumIcon(int nPriority = ULT_ICON_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMediumIcon()override;
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