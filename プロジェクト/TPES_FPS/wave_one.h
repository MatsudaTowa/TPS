//=============================================
//
//1�E�F�[�u����[wave_one.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_ONE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_ONE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  1�E�F�[�u�N���X��`
//=============================================
class CWave_One :public CWave
{
public:
	static const std::string WAVE_1_ENEMY_FILE;	//�E�F�[�u1�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_1_BLOCK_FILE;	//�E�F�[�u1�̃u���b�N�̃t�@�C��
	static const std::string WAVE_1_WALL_FILE;	//�E�F�[�u1�̕ǂ̃t�@�C��

	CWave_One();
	~CWave_One()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

