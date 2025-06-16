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

//=============================================
// �Q�[���N���X
//=============================================
class CGame:public CScene
{
public:

	enum GAME_STATE
	{
		GAME_STATE_NORMAL = 0,
		GAME_STATE_MAX,
	};

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	static const int DELAY_CNT = 30; //���U���g�ɔ�Ԃ܂ł̃f�B���C
	static const int BLOCK_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����

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
	 * @brief ��Ԑݒ�
	 * @param [in]���
	 */
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	/**
	 * @brief �X�e�[�g�擾
	 * @return �X�e�[�g
	 */
	static GAME_STATE&GetState();
	/**
	 * @brief �v���C���[�擾
	 * @return �v���C���[
	 */
	CPlayer*GetPlayer();

	/**
	 * @brief �E�F�[�u�擾
	 * @return �E�F�[�u
	 */
	static CWave*GetWave();

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
	static void SetWave(CWave::WAVE wave,CWave::WAVE next_wave,const char* ResultFile);
private:
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��

	static const int DELAY_FLAME = 60; //�f�B���C�̃t���[����
	static const int DEATH_PENALTY = -50; //���񂾂Ƃ��̃y�i���e�B

	/**
	 * @brief ���S�y�i���e�B�v�Z
	 */
	void ApplyDeathPenalty();

	int m_nResultDelay; //���U���g�ւ̃f�B���C
	static GAME_STATE m_GameState; //�Q�[���X�e�[�g
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	CPlayer*m_pPlayer;
	static CWave* m_pWave;

	CWave::WAVE m_next_wave;
};
#endif