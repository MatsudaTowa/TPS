//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
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
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void ApplyDeathPenalty();
	void Draw() override;
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	static GAME_STATE&GetState();

	static CPlayer*GetPlayer();
	static CWave*GetWave();
	//�E�F�[�u�ݒ�
	static void SetWave(CWave::WAVE wave);

	static void SetWave(CWave::WAVE wave,CWave::WAVE next_wave,const char* ResultFile);
private:
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��

	static const int DELAY_FLAME = 60; //�f�B���C�̃t���[����
	static const int DEATH_PENALTY = -50; //���񂾂Ƃ��̃y�i���e�B
	int m_nResultDelay; //���U���g�ւ̃f�B���C
	bool m_bEdit; //�G�f�B�b�g���Ă邩�ǂ���
	static GAME_STATE m_GameState; //�Q�[���X�e�[�g
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	static CPlayer*m_pPlayer;
	static CWave* m_pWave;

	CWave::WAVE m_next_wave;

	void LoadBlock(const std::string* pFileName);
};
#endif