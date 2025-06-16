//=============================================
//
//�v���C���[[player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"

//=============================================
//�v���C���[�N���X
//=============================================
class CPlayer:public CCharacter
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int PLAYER_PRIORITY = 8; //�`�揇

	//���[�V�����̎�ނ̗�
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CPlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CPlayer();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
	/**
	 * @brief �`��
	 */
	void Draw();

	/**
	 * @brief �v���C���[����
	 * @param [in]�v���C���[�|�C���^
	 * @return �v���C���[�|�C���^
	 */
	static CPlayer* Create(CPlayer* player);
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //�X�|�[���ʒu
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //�X�|�[������

	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y

	/**
	 * @brief �f�o�b�O�\��
	 */
	void DebugPos();
};
#endif