//=============================================
//
//�E���g�͈͏���[ult_range.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "ult_effect.h"

#ifndef _ULT_RANGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ULT_RANGE_H_

//=============================================
// �E���g�͈̔̓N���X
//=============================================
class CUltRange
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CUltRange();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUltRange();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();

	/**
	 * @brief ����
	 * @param [in]�ʒu
	 * @return �E���g�͈̔̓|�C���^
	 */
	static CUltRange* Create(D3DXVECTOR3 pos);

	/**
	 * @brief �������Ԏ擾
	 * @return ��������
	 */
	inline int& GetLife()
	{
		return m_nLife;
	}
private:
	static const int LIFE = 10;
	static const int MAX_DAMAGE =10;
	static constexpr float RADIUS = 20.0f;
	D3DXVECTOR3 m_pos;
	int m_nLife;

	CUltEffect* m_pUltEffect;
};

#endif