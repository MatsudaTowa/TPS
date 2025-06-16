//=============================================
//
//�^�C�g������[title.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "block.h"
#include "title_screen.h"

//=============================================
//�^�C�g���N���X
//=============================================
class CTitle :public CScene
{
public:
	static const int BLOCK_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	/**
	 * @brief �R���X�g���N�^
	 */
	CTitle();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CTitle() override;
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
private:
	static const int NUM_SCREEN = 2;	//����UI��u����
	static const D3DXVECTOR3 LOGO_POS; //���S�̈ʒu
	static const D3DXVECTOR3 UI_POS; //UI�̈ʒu

	static const D3DXVECTOR3 FIELD_SIZE; //���̃T�C�Y
	static const D3DXVECTOR2 LOGO_SIZE; //���S�̃T�C�Y
	static const D3DXVECTOR2 UI_SIZE; //UI�T�C�Y

	static const D3DXVECTOR3 PLAYER_SPAWN; //�X�|�[���ʒu

	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	//�v���C���[
	CPlayer*m_pPlayer;

	CTitle_Screen*m_pTitleScreen[NUM_SCREEN];
};
#endif