//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBossWandering::CBossWandering()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossWandering::~CBossWandering()
{
}

//=============================================
//�p�j
//=============================================
void CBossWandering::Wandering(CEnemy* enemy)
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossChase::CBossChase()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossChase::~CBossChase()
{
}

//=============================================
//�ǐ�
//=============================================
void CBossChase::Chase(CEnemy* enemy)
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CBossAttack::CBossAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossAttack::~CBossAttack()
{
}

//=============================================
//�U��
//=============================================
void CBossAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	//if (m_nStateChangeCnt < SHOT_STATE_FRAME)
	//{
	//	CEnemyAttack::Attack(Allegiance, type, character);
	//	++m_nStateChangeCnt;
	//}
	//if (m_nStateChangeCnt >= SHOT_STATE_FRAME)
	//{
	//	m_nStateChangeCnt = 0;
	//	//�ړ���Ԃɐ؂�ւ�
	//	character->ChangeState(new CMoveState);
	//}
}
