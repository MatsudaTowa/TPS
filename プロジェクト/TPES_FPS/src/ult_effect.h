//=============================================
//
//�E���g�G�t�F�N�g�uult_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ULT_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_EFFECT_H_
#include "main.h"
#include "object3D.h"

//=============================================
//�E���g�G�t�F�N�g�N���X
//=============================================
class CUltEffect : public CObject3D
{
public:
	static const int PRIORITY = 12; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CUltEffect(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUltEffect()override;
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
	 * @return �E���g�̃G�t�F�N�g�|�C���^
	 */
	static CUltEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const D3DXCOLOR COLOR;	//�F
};
#endif