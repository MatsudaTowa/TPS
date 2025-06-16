//=============================================
// 
//�G���p�j����ۂɌ������|�C���g[move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOVE_POINT_
#include "main.h"
#include "billboard.h"

//=============================================
// �T���|�C���g�N���X
//=============================================
class CMovePoint : public CBillboard
{
public:
	static const int POINT_PRIORITY = 8; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CMovePoint(int nPriority = POINT_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMovePoint() override;
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
	 * @return �ړ��|�C���g�̃|�C���^
	 */
	static CMovePoint* Create(D3DXVECTOR3 pos);

	/**
	 * @brief ���擾
	 * @return �|�C���g�̐�
	 */
	static int& GetNumPoint()
	{
		return m_NumPoint;
	};
private:
	static constexpr float POINT_SIZE = 10.0f; //�T�C�Y

	static int m_NumPoint; //�����邩
};
#endif