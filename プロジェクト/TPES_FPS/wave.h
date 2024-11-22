//=============================================
//
//�E�F�[�u����[wave.h]
//Auther Matsuda Towa
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
	static const int TXT_MAX = 1024; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
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

	// �����o�֐�
	CWave();
	virtual ~CWave();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	static CWave* Create(WAVE wave);
	static CWave* Create(WAVE wave,WAVE next_wave,const char* ResultFile);
	static WAVE GetCurrentWave();
	static CScore* GetScore();

	void LoadBlock(const std::string* pFileName);
	void LoadWall(const std::string* pFileName);
	void LoadEnemy(const std::string* pFileName);

	void SetWaveScore(int nScore);

	int GetWaveScore();

	//�E�F�[�u�̃��U���g�e���v���[�g���\�b�h
	void WaveResult(const std::string* pFileName)
	{
		m_pScore->ExportScore(pFileName);
		m_pScore->Reset();
	}
protected:
	// �����o�ϐ�
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��
	LOAD_WALL m_LoadWall; //�ǂݍ��ނƂ��ɕK�v�ȕǂ̏��
	LOAD_POINT m_LoadPoint; //�ǂݍ��ނƂ��ɕK�v�ȃ|�C���g�̏��

	int m_nScore; //�X�R�A�i�[�ϐ�
	static CScore* m_pScore;
	static WAVE m_next; //���̃E�F�[�u
	static const char* m_ResultFile; //���U���g�t�@�C��
	static WAVE m_CurrentWave; //���݂̃E�F�[�u
};

#endif