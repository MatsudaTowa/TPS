//=============================================
//
//��[field.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//=============================================
// ���N���X
//=============================================
class CField : public CObject3D
{
public:

	static const int FIELD_PRIORITY = 3; //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CField(int nPriority = FIELD_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CField()override;
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
	 * @return ���̃|�C���^
	 */
	static CField* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif