//=============================================
//
//�ʏ�̓G�̏���[normal_enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _NORMAL_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"

//=============================================
//�ʏ�̃G�l�~�[�N���X
//=============================================
class CNormalEnemy :public CEnemy
{
public:
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
	static const int DEFAULT_LIFE = 80; //���C�t

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
	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CNormalEnemy() override;
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

	/**
	 * @brief �E���g�̃q�b�g����
	 * @param [in]�E���g�̈ʒu
	 * @param [in]�_���[�W
	 */
	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
private:

	//�G�l�~�[�̈ړ��֘A
	static const D3DXVECTOR3 SHADOW_SIZE; //�e�̃T�C�Y

	Motion_Type m_Motion; //���[�V�����̎��
};

#endif