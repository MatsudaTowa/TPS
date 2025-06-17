//=============================================
//
//�Q�[������[game.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"
#include "game_state.h"

//=============================================
// �Q�[���N���X
//=============================================
class CGame:public CScene
{
public:

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	static const int DELAY_CNT = 30; //���U���g�ɔ�Ԃ܂ł̃f�B���C
	static const int BLOCK_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	static const int DELAY_FLAME = 60; //�f�B���C�̃t���[����

	/**
	 * @brief �R���X�g���N�^
	 */
	CGame();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CGame() override;
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
	 * @brief ���S�y�i���e�B�v�Z
	 */
	void ApplyDeathPenalty();

	/**
	 * @brief �I�u�W�F�N�g�̍X�V���s��������
	 * @param [in]���������ǂ���
	 */
	void UpdateObjectDecision(bool isActive);

	/**
	 * @brief �E�F�[�u�擾
	 * @return �E�F�[�u
	 */
	static inline CWave* GetWave()
	{
		return m_pWave;
	}

	/**
	 * @brief ���̃E�F�[�u�擾
	 * @return ���̃E�F�[�u
	 */
	inline CWave::WAVE GetNextWave()
	{
		return m_next_wave;
	}

	/**
	 * @brief ���̃E�F�[�u�ݒ�
	 * @param [in]���̃E�F�[�u
	 */
	inline void SetNextWave(CWave::WAVE next_wave)
	{
		m_next_wave = next_wave;
	}

	/**
	 * @brief ���U���g�J�ڂ̗]�C�J�E���g�擾
	 * @param ���U���g�J�ڂ̗]�C�J�E���g
	 */
	inline int GetResultDelay()
	{
		return m_nResultDelay;
	}
	/**
	 * @brief ���U���g�J�ڂ̗]�C�J�E���g�ݒ�
	 * @param [in]���U���g�J�ڂ̗]�C�J�E���g
	 */
	inline void SetResultDelay(int nResultDelay)
	{
		m_nResultDelay = nResultDelay;
	}

	/**
	 * @brief ���͉\���擾
	 * @param ���͉\��
	 */
	inline bool GetPauseKey()
	{
		return m_nPauseCnt >= PAUSE_POSSIBLE_FLAME;
	}

	/**
	 * @brief �J�E���g���Z�b�g
	 */
	inline void ResetPauseCnt()
	{
		m_nPauseCnt = 0;
	}

	/**
	 * @brief �X�e�[�g�ύX
	 * @param [in]���̃X�e�[�g
	 */
	void ChangeState(CGameState* state);

	/**
	 * @brief �E�F�[�u�ݒ�
	 * @param [in]wave
	 */
	static void SetWave(CWave::WAVE wave);

	/**
	 * @brief �E�F�[�u�ݒ�
	 * @param [in]�E�F�[�u
	 * @param [in]���̃E�F�[�u
	 * @param [in]���U���g�̃X�R�A�t�@�C��
	 */
	static void SetWave(CWave::WAVE wave, CWave::WAVE next_wave, const char* ResultFile);

private:
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��

	static const int DEATH_PENALTY = -50; //���񂾂Ƃ��̃y�i���e�B
	static const int PAUSE_POSSIBLE_FLAME = 1;	//�|�[�Y��L����������t���[��

	int m_nResultDelay; //���U���g�ւ̃f�B���C
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	int m_nPauseCnt;	//�|�[�Y��L�������鎞�ɗp����J�E���g

	CGameState* m_pState;

	static CWave* m_pWave;

	CWave::WAVE m_next_wave;
};
#endif