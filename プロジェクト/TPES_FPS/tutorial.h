//=============================================
//
//3DTemplate[tutorial.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TUTORIAL_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"
#include "tutorial_UI.h"

class CTutorial:public CScene
{
public:
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

	static const std::string ENEMY_FILE;	//�G�l�~�[�̃t�@�C��
	static const std::string BLOCK_FILE;	//�u���b�N�̃t�@�C��
	static const std::string WALL_FILE;		//�ǂ̃t�@�C��
	static const int TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	CTutorial();
	~CTutorial() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��
	LOAD_WALL m_LoadWall; //�ǂݍ��ނƂ��ɕK�v�ȕǂ̏��

	CTutorial_UI* m_pTutorial_UI;

	void LoadBlock(const std::string* pFileName);
	void LoadWall(const std::string* pFileName);
	void LoadEnemy(const std::string* pFileName);
};
#endif