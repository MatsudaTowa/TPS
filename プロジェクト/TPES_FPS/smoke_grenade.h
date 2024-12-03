//=============================================
//
//�X���[�N�O���l�[�h����[somoke_grenade.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_GRENADE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_GRENADE_H_

class CSmokeGrenade : public CObjectX
{
public:
	static const int SMOKE_PRIORITY = 24; //�`�揇

	CSmokeGrenade(int nPriority = SMOKE_PRIORITY);
	~CSmokeGrenade()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�X���[�N�O���l�[�h�쐬
	static CSmokeGrenade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//���f���̖��O
	static const int CREATE_SMOKE_NUM = 100; //��������X���[�N�̐�
	void HitField();
	D3DXVECTOR3 m_oldpos;
	D3DXVECTOR3 m_move;
	bool m_bBoot; //�O���l�[�h���N��������
	int m_NumCreate; //�������������J�E���g����ϐ�
};

#endif