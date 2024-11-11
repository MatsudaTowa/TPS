//=============================================
//
//�L�����N�^�[�̃X�g���e�W�[�p�^�[��[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#include "character_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CMove::CMove()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMove::~CMove()
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CDush::CDush()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CDush::~CDush()
{
}

//=============================================
//�ړ�����
//=============================================
void CDush::Move(float fSpeed, D3DXVECTOR3 vecDirection, float fRotMoveY, CCharacter* character, int motion)
{
	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(fRotMoveY) * fSpeed;
		move.z += cosf(fRotMoveY) * fSpeed;
	}
	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = fRotMoveY + D3DX_PI;
	//rot����
	character->SetRot(rot);
	//�ړ��ʑ��
	character->SetMove(move);
	//���[�V�������
	character->SetMotion(motion);
}
