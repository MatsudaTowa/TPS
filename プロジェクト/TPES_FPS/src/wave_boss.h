//=============================================
//
//�{�X�E�F�[�u����[wave_boss.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_BOSS_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_BOSS_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "move_point.h"

//=============================================
//  �{�X�E�F�[�u�N���X��`
//=============================================
class CWave_Boss :public CWave
{
public:
	static const int NUM_POINT = 12;

	/**
	 * @brief �R���X�g���N�^
	 */
	CWave_Boss();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CWave_Boss()override;
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
	 * @brief �ړ���擾
	 * @param [in]�ԍ�
	 * @return �ړ���|�C���^
	 */
	static CMovePoint* GetMovePoint(int Idx);
private:
	static const std::string WAVE_BOSS_ENEMY_FILE;	//�E�F�[�u�{�X�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_BOSS_BLOCK_FILE;	//�E�F�[�u�{�X�̃u���b�N�̃t�@�C��
	static const std::string WAVE_BOSS_WALL_FILE;	//�E�F�[�u�{�X�̕ǂ̃t�@�C��
	static const std::string WAVE_BOSS_POINT_FILE;	//�E�F�[�u�{�X�|�C���g�̃t�@�C��

	/**
	 * @brief �ړ���ǂݍ���
	 * @param [in]�t�@�C���l�[��
	 */
	void LoadPoint(const std::string* pFileName);
	static CMovePoint* m_pMovePoint[NUM_POINT];
};

#endif

