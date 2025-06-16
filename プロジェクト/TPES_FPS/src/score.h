//=============================================
//
//�X�R�A�����uscorer.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SCORE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"

//=============================================
//�X�R�A�N���X
//=============================================
class CScore
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CScore();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CScore();
	/**
	 * @brief ������
	 * @return ����������
	 */
	virtual HRESULT Init();
	/**
	 * @brief �I��
	 */
	virtual void Uninit();
	/**
	 * @brief �X�V
	 */
	virtual void Update();
	/**
	 * @brief �X�R�A���Z
	 * @param [in]�l
	 */
	void AddScore(int nValue);
	/**
	 * @brief �X�R�A�����o��
	 * @param [in]�t�@�C���l�[��
	 */
	void ExportScore(const std::string& FileName);

	/**
	 * @brief �X�R�A���Z�b�g
	 */
	void Reset();

	/**
	 * @brief �X�R�A�ݒ�
	 * @param [in]�X�R�A
	 */
	void SetScore(int nScore);

	/**
	 * @brief �X�R�A�擾
	 * @return ���݂̃X�R�A
	 */
	inline int GetScore()
	{
		return m_nScore;
	}

	/**
	 * @brief �ʒu�ݒ�
	 * @param [in]�ʒu
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief �T�C�Y�ݒ�
	 * @param [in]�T�C�Y
	 */
	inline void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	/**
	 * @brief ���̈ʒu���炷�l�ݒ�
	 * @param [in]���̈ʒu���炷�l
	 */
	inline void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	/**
	 * @brief �\�����W�擾
	 * @return �\�����W
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief �T�C�Y�擾
	 * @return �T�C�Y
	 */
	inline D3DXVECTOR2& GetSize()
	{
		return m_size;
	}

	/**
	 * @brief �����炷�l�擾
	 * @return �����炷�l
	 */
	inline float& GetDigitShift()
	{
		return m_DigitShift;
	}
private:
	static const int NUM_DIGIT = 6;  //����

	static const D3DXVECTOR3 NUM_POS; //�����̈ʒu
	static const D3DXVECTOR2 NUM_SIZE; //�����̃T�C�Y

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
	CNumber_2D* m_pNumber[NUM_DIGIT];

	float m_DigitShift;
	int m_nScore; //�X�R�A�̒l

};
#endif // DEBUG