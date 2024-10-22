//=============================================
//
//�v���C���[����[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "character.h"
#include "manager.h"
//�v���C���[�N���X
class CPlayer : public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //�`�揇

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	static bool m_PlayerDeath;

private:
	static const std::string MODEL_NAME;	//���f���̖��O

	//�v���C���[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int MAX_JUMPCNT; //�W�����v��
	static const int STATE_FRAME; //�X�e�[�g�ύX�t���[����
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void ReSpawn(); //���X�|�[��
	void PlayerMove(); //�v���C���[�ړ�����

	int m_nJumpCnt; //�W�����v�J�E���g

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����

	void DebugPos();

	float fSpeed;
	float fJump;
	float fRadius;
	float fHeight;
};
#endif