//=============================================
//
//ult�����܂����Ƃ��ɃA�C�R������o���G�t�F�N�g[ult_icon_effect.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "Object2D_anim.h"

#ifndef _ULT_ICON_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_ICON_EFFECT_H_

//=============================================
// ULT�̃A�C�R���G�t�F�N�g�N���X
//=============================================
class CUltIconEffect : public CObject2D_Anim
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int PRIORITY = 20; //�`�揇
	static const int TEX_SPLIT_X = 4; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y = 1; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME = 10; //�A�j���[�V�����t���[����

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CUltIconEffect(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUltIconEffect()override;
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
	 * @return �E���g�����܂������̃G�t�F�N�g�|�C���^
	 */
	static CUltIconEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
};
#endif