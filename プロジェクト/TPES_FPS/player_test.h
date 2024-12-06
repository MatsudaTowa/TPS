//=============================================
//
//3DTemplate[player_test.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_TEST_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_TEST_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "reticle.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "player_behavior.h"
#include "enemy.h"
#include "hit_camera_effect.h"

class CPlayerSliding;
//�v���C���[�N���X
class CPlayer_test:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int PLAYER_LIFE = 100; //�̗�
	static const int PLAYER_PRIORITY = 8; //�`�揇
	static const int PARTS_PARENT[NUM_PARTS]; //�p�[�c��

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //�X�|�[���ʒu
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //�X�|�[������
	//���[�V�����̎�ނ̗�
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	}Motion_Type;

	CPlayer_test(int nPriority = PLAYER_PRIORITY);
	~CPlayer_test();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//�v���C���[�쐬
	static CPlayer_test* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	void ResetRot(); //�����̃��Z�b�g

	void ColisionEnemy(); //�G�Ƃ̓����蔻��

	void ChangeDamageState(); //TODO�L�����N�^�[�ɂ܂Ƃ߂�

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

private:

	//�v���C���[�̈ړ��֘A
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const int MAX_JUMPCNT; //�W�����v��
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void ReSpawn(); //���X�|�[��
	void Input(); //�v���C���[���͏���
	static CAmmo_UI*m_pAmmoUI;
	static CLife_UI*m_pLifeUI;

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	CReticle* m_Raticle;

	CPlayerSliding* m_pSliding;

	CHitCameraEffect* m_pHitCameraEffect;

	void DebugPos();

	bool m_bRelorad; //�����[�h���邩�ǂ���

	bool m_bSmoke; //�X���[�N���g������
};
#endif