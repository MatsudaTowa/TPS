//=============================================
//
//�q�b�g�}�[�J�[[hitmaker.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _HITMAKER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _HITMAKER_H_

//=============================================
//�q�b�g�}�[�J�[�N���X
//=============================================
class CHitMaker : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 18; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CHitMaker(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CHitMaker()override;
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
	 * @param [in]�T�C�Y
	 * @param [in]�F
	 * @return �q�b�g�}�[�J�[�̃|�C���^
	 */
	static CHitMaker* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string HITMARKER_DOT_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int HITMARKER_LIFE = 30; //�̗�

	static constexpr float FADE_OUT = 0.05f; //�A���t�@�l����

	/**
	 * @brief �F�ݒ�
	 * @param [in]�F
	 */
	void HitColor(D3DXCOLOR col);

	int m_nLife;
};

#endif