//=============================================
//
//2�E�F�[�u����[wave_two.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_TWO_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_TWO_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  2�E�F�[�u�N���X��`
//=============================================
class CWave_Two :public CWave
{
public:
	static const std::string WAVE_2_ENEMY_FILE;	//�E�F�[�u2�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_2_BLOCK_FILE;	//�E�F�[�u2�̃u���b�N�̃t�@�C��
	static const std::string WAVE_2_WALL_FILE;	//�E�F�[�u2�̕ǂ̃t�@�C��

	CWave_Two();
	~CWave_Two()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

