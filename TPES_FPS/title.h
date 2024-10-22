//=============================================
//
//3DTemplate[title.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "block.h"
#include "title_screen.h"
class CTitle :public CScene
{
public:
	static const int BLOCK_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	void LoadBlock(const std::string* pFileName);

	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	//�v���C���[
	CPlayer*m_pPlayer;

	CTitle_Screen*m_pTitleScreen[2];
};
#endif