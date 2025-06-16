//=============================================
// 
//�}�Y���t���b�V��[muzzle_flash.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MUZZLE_FLASH_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MUZZLE_FLASH_H_
#include "main.h"
#include "billboard.h"

//=============================================
// �}�Y���t���b�V���N���X
//=============================================
class CMuzzleFlash : public CBillboard
{
public:
	static const int PRIORITY = 10; //�`�揇
	static const int LIFE = 10; //���C�t
	static const D3DXVECTOR3 SIZE; //�T�C�Y

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMuzzleFlash(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMuzzleFlash() override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
	/**
	 * @brief �X�V
	 */
	void Update() override;
	/**
	 * @brief �`��
	 */
	void Draw() override;
	/**
	 * @brief ����
	 * @param [in]�ʒu
	 * @return �}�Y���t���b�V���̃|�C���^
	 */
	static CMuzzleFlash* Create(D3DXVECTOR3 pos);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	int m_nLife;
};
#endif