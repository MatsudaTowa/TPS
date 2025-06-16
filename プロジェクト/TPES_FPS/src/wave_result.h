//=============================================
//
//�E�F�[�u���Ƃ̌���[wave_result.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_RESULT_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "wave_score.h"
#include"wave_result_screen.h"

//=============================================
//  �E�F�[�u���U���g�N���X��`
//=============================================
class CWave_Result:public CWave
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CWave_Result();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CWave_Result() override;
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
	 * @brief ���̃E�F�[�u�ݒ�
	 * @param [in]�E�F�[�u
	 */
	void SetNextWave(CWave::WAVE wave);
	/**
	 * @brief �X�R�A�ǂݍ���
	 * @param [in]�X�R�A�ۑ��t�@�C���l�[��
	 */
	void LoadScore(const std::string& pFileName);

	/**
	 * @brief ����
	 * @param [in]�E�F�[�u
	 * @param [in]�t�@�C���l�[��
	 */
	inline void Create(CWave::WAVE wave, char* pFileName)
	{
		SetNextWave(wave);
	}
private:
	int m_nScore;
	CWave_Result_Screen* m_pScreen;
};

#endif

