//=============================================
//
//�E�F�[�u����[wave.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include "score.h"
#include"field.h"

//=============================================
//  �E�F�[�u�N���X��`
//=============================================
class CWave
{
public:
	static const int TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	//�E�F�[�u��
	enum WAVE
	{
		NONE = 0,
		ONE,
		TWO,
		THREE,
		BOSS,
		RESULT,
		MAX,
	};

	//�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̍\����
	struct LOAD_ENEMY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	};

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	//�ǂݍ��ނƂ��ɕK�v�ȕǂ̍\����
	struct LOAD_WALL
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
	};

	//�ǂݍ��ނƂ��ɕK�v�ȃ|�C���g�̍\����
	struct LOAD_POINT
	{
		D3DXVECTOR3 pos;
	};

	/**
	 * @brief �R���X�g���N�^
	 */
	CWave();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CWave();

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
	 * @brief ����
	 * @param [in]�E�F�[�u
	 * @return �E�F�[�u�|�C���^
	 */
	static CWave* Create(WAVE wave);
	/**
	 * @brief ����
	 * @param [in]�E�F�[�u
	 * @param [in]���̃E�F�[�u
	 * @param [in]���U���g�t�@�C���l�[��
	 * @return �E�F�[�u�|�C���^
	 */
	static CWave* Create(WAVE wave,WAVE next_wave,const char* ResultFile);
	/**
	 * @brief ���݂̃E�F�[�u�擾
	 * @return ���E�F�[�u�ڂ�
	 */
	static WAVE GetCurrentWave();
	/**
	 * @brief �X�R�A�擾
	 * @return �X�R�A
	 */
	static CScore* GetScore();

	/**
	 * @brief �u���b�N�ǂݍ���
	 * @param [in]�t�@�C���l�[��
	 */
	void LoadBlock(const std::string& pFileName);

	/**
	 * @brief �Ǔǂݍ���
	 * @param [in]�t�@�C���l�[��
	 */
	void LoadWall(const std::string* pFileName);

	/**
	 * @brief �G�ǂݍ���
	 * @param [in]�t�@�C���l�[��
	 */
	void LoadEnemy(const std::string* pFileName);

	/**
	 * @brief �E�F�[�u�̃X�R�A�ݒ�
	 * @param [in]�X�R�A
	 */
	inline void SetWaveScore(int nScore)
	{
		m_nTotalScore = nScore;
	}

	/**
	 * @brief �X�R�A�擾
	 * @return �X�R�A
	 */
	inline int GetWaveScore()
	{
		return m_nTotalScore;
	}

	/**
	 * @brief �E�F�[�u�̃��U���g����
	 * @param [in]���U���g�t�@�C��
	 */
	inline void WaveResult(const std::string& pFileName)
	{
		m_pScore->ExportScore(pFileName);
		m_pScore->Reset();
	}
protected:
	static const D3DXVECTOR3 NORMAL_FIELD_SIZE; //�ʏ�E�F�[�u���̃T�C�Y
	static const D3DXVECTOR3 BOSS_FIELD_SIZE; //�{�X�E�F�[�u���̃T�C�Y
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��
	LOAD_WALL m_LoadWall; //�ǂݍ��ނƂ��ɕK�v�ȕǂ̏��
	LOAD_POINT m_LoadPoint; //�ǂݍ��ނƂ��ɕK�v�ȃ|�C���g�̏��

	int m_nTotalScore; //�X�R�A�i�[�ϐ�
	static CScore* m_pScore;
	static WAVE m_next; //���̃E�F�[�u
	static const char* m_ResultFile; //���U���g�t�@�C��
	static WAVE m_CurrentWave; //���݂̃E�F�[�u
};

#endif