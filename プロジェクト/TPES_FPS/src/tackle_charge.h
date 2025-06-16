//=============================================
//
//�^�b�N���`���[�W���̃G�t�F�N�g[tackle_charge.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _TACKLE_CHARGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TACKLE_CHARGE_H_

//=============================================
// �^�b�N���`���[�W�G�t�F�N�g�N���X
//=============================================
class CTackleCharge : public CBillboard
{
public:
	static const int PRIORITY = 10; //�`�揇
	static const D3DXVECTOR3 SIZE; //�T�C�Y
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CTackleCharge(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTackleCharge()override;
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
	 * @return �^�b�N���`���[�W���G�t�F�N�g�|�C���^
	 */
	static CTackleCharge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);

private:
	static const std::string TEXTURE_NAME; //�e�N�X�`���̖��O
};

#endif