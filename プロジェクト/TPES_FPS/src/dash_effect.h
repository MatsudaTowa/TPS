//=============================================
//
//�_�b�V�����ɃL�����N�^�[�̑O���ɏo���G�t�F�N�g[dash_effect.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DASH_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _DASH_EFFECT_H_
#include "main.h"
#include "objectX.h"

//=============================================
//�^�b�N���G�t�F�N�g�N���X
//=============================================
class CDashEffect : public CObjectX
{
public:
	static const int PRIORITY = 11; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CDashEffect(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CDashEffect()override;
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
	 * @param [in]����
	 * @return �G�t�F�N�g�|�C���^
	 */
	static CDashEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	static const char* MODEL_NAME;	//���f���̖��O
	static const D3DXVECTOR3 SCALE;
	static const D3DXCOLOR COLOR;

};
#endif