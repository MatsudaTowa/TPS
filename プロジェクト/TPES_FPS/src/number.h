//=============================================
//
//�����Ǘ��unumber.h�v
// Author���c�i�v
//
//=============================================
#ifndef _NUMBER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"
#include "billboard.h"

//=============================================
//�i���o�[�N���X2D
//=============================================
class CNumber_2D:public CObject2D
{
public:
	static const int NUMBER_PRIORITY = 21;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CNumber_2D(int nPriority = NUMBER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CNumber_2D()override;
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
	 * @return �i���o�[2D
	 */
	static CNumber_2D* Create(D3DXVECTOR3 pos ,D3DXVECTOR2 size);

	/**
	 * @brief �����̐ݒ�
	 * @param [in]�����̍ŏ����W
	 * @param [in]�����̍ő���W
	 * @param [in]�F
	 */
	void SetNumber(float fNumPos1,float fNumPos2,D3DXCOLOR col);
	/**
	 * @brief �����̒��_����
	 */
	void NumberVtx();

private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	D3DXVECTOR2 m_mintex; //�e�N�X�`���̍ŏ����W
	D3DXVECTOR2 m_maxtex; //�e�N�X�`���̍ő���W
	D3DXCOLOR m_col; //�J���[
};

//=============================================
//�i���o�[�N���X3D
//=============================================
class CNumber_3D :public CBillboard
{
public:
	static const int NUMBER_PRIORITY = 20;  //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CNumber_3D(int nPriority = NUMBER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CNumber_3D()override;
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
	 * @return �i���o�[3D�̃|�C���^
	 */
	static CNumber_3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	/**
	 * @brief �����̐ݒ�
	 * @param [in]�����̍ŏ����W
	 * @param [in]�����̍ő���W
	 * @param [in]�F
	 */
	void SetNumber(float fNumPos1, float fNumPos2, D3DXCOLOR col);
	/**
	 * @brief �����̒��_����
	 */
	void NumberVtx();

private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	D3DXVECTOR2 m_mintex; //�e�N�X�`���̍ŏ����W
	D3DXVECTOR2 m_maxtex; //�e�N�X�`���̍ő���W
	D3DXCOLOR m_col; //�J���[
};

#endif // DEBUG