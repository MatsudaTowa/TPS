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

//=============================================
//  �E�F�[�u�N���X��`
//=============================================
class CWave
{
public:
	static const std::string WAVE_1_ENEMY_FILE;	//�E�F�[�u1�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_2_ENEMY_FILE;	//�E�F�[�u2�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_3_ENEMY_FILE;	//�E�F�[�u3�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_BOSS_ENEMY_FILE;	//�E�F�[�uBoss�̃G�l�~�[�̃t�@�C��

	static const std::string WAVE_1_BLOCK_FILE;	//�E�F�[�u1�̃u���b�N�̃t�@�C��
	static const std::string WAVE_2_BLOCK_FILE;	//�E�F�[�u2�̃u���b�N�̃t�@�C��
	static const std::string WAVE_3_BLOCK_FILE;	//�E�F�[�u3�̃u���b�N�̃t�@�C��
	static const std::string WAVE_BOSS_BLOCK_FILE;	//�E�F�[�uBoss�̃u���b�N�̃t�@�C��

	static const int TXT_MAX = 1024; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	//�E�F�[�u��
	enum class WAVE
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
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	}LOAD_ENEMY;

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	// �����o�֐�
	CWave();
	~CWave();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetWave();
	WAVE GetWave();
private:

	void LoadBlock(const std::string* pFileName);
	void LoadEnemy(const std::string* pFileName);
	// �����o�ϐ�
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	WAVE m_CurrentWave; //���݂̃E�F�[�u
};
#endif