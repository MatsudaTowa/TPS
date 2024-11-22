//=============================================
//
//�{�X�E�F�[�u����[wave_boss.h]
//Auther Matsuda Towa
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
	static const std::string WAVE_BOSS_ENEMY_FILE;	//�E�F�[�u�{�X�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_BOSS_BLOCK_FILE;	//�E�F�[�u�{�X�̃u���b�N�̃t�@�C��
	static const std::string WAVE_BOSS_WALL_FILE;	//�E�F�[�u�{�X�̕ǂ̃t�@�C��
	static const std::string WAVE_BOSS_POINT_FILE;	//�E�F�[�u�{�X�|�C���g�̃t�@�C��

	static const int NUM_POINT = 9;

	CWave_Boss();
	~CWave_Boss()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	//�ړ���擾
	static CMovePoint* GetMovePoint(int Idx);
private:
	void LoadPoint(const std::string* pFileName);
	static CMovePoint* m_pMovePoint[NUM_POINT];
};

#endif

