//=============================================
//
//�ǂ̏���[wall.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WALL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WALL_H_
#include "main.h"
#include "object3D.h"

//=============================================
//�ǃN���X
//=============================================
class CWall : public CObject3D
{
public:
	static const int WALL_PRIORITY = 3; //�`�揇
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CWall(int nPriority = WALL_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CWall()override;
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
	 * @return �ǂ̃|�C���^
	 */
	static CWall* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
};
#endif