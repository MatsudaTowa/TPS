//=============================================
//
//3�E�F�[�u����[wave_three.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_THREE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_THREE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  3�E�F�[�u�N���X��`
//=============================================
class CWave_Three :public CWave
{
public:
	static const std::string WAVE_3_ENEMY_FILE;	//�E�F�[�u3�̃G�l�~�[�̃t�@�C��
	static const std::string WAVE_3_BLOCK_FILE;	//�E�F�[�u3�̃u���b�N�̃t�@�C��
	static const std::string WAVE_3_WALL_FILE;	//�E�F�[�u3�̕ǂ̃t�@�C��

	CWave_Three();
	~CWave_Three()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

