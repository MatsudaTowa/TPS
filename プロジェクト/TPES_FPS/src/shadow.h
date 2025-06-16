//=============================================
//
//�e�ushadow.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SHADOW_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//=============================================
//�e�N���X
//=============================================
class CShadow : public CObject3D
{
public:
	static const int SHADOW_PRIORITY = 9; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CShadow(int nPriority = SHADOW_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CShadow()override;
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
	 * @return �e�̃|�C���^
	 */
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif