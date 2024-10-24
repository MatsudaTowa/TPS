//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BULLET_H_

class CBullet : public CAttack_Manager
{
public:
	static const std::string BULLET_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int BULLET_PRIORITY = 24; //�`�揇

	//�G���������̔��f�����
	typedef enum
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	}BULLET_ALLEGIANCE;

	//�e�̎��
	typedef enum
	{
		BULLET_TYPE_NORMAL = 0,
		BULLET_TYPE_MAX,
	}BULLET_TYPE;

	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void OnActive();

	//�e�쐬
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot,
	D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type);

	//�ړ��ʐݒ�
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//�^�C�v�ݒ�
	void SetBulletType(BULLET_TYPE type)
	{
		m_type = type;
	}

	//�G���������̐ݒ�
	void SetBulletAllegiance(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}

	D3DXVECTOR3 GetMove();

	BULLET_ALLEGIANCE GetBulletAllegiance();
private:
	BULLET_ALLEGIANCE m_Allegiance; //�G���������𔻒f����񋓌^�ϐ�
	BULLET_TYPE m_type; //�e�̎��
	D3DXVECTOR3 m_move; //�ړ���
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};

#endif