//=============================================
//
//�{�X�̃X�g���e�W�[�p�^�[��[enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_behavior.h"
#include "wave_boss.h"
#include "player_test.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBossWandering::CBossWandering():m_MoveIdx(0), m_StopCnt(0), m_isMove()
{
	m_isMove = true;
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
void CBossWandering::Wandering(CBossEnemy* boss)
{
	if (m_isMove)
	{
		//�ړ���̏��擾(�������ړ���̃|�C���g�̔z��ԍ�)
		CMovePoint* pMovePoint = CWave_Boss::GetMovePoint(m_MoveIdx);

		//�Ώۂ̈ʒu�ւ̕������
		D3DXVECTOR3 point = { pMovePoint->GetPos().x - boss->GetPos().x,0.0f,pMovePoint->GetPos().z - boss->GetPos().z };

		// �ړI�n�Ƃ̋������v�Z
		float distance = sqrtf(point.x * point.x + point.z * point.z);

		// ���B����p��臒l
		const float threshold = 0.5f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j

		// �܂��ړI�n�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ��������s��
		if (distance > threshold)
		{
			//�Ώە��Ƃ̊p�x�v�Z
			float angle = atan2f(point.x, point.z);

			D3DXVECTOR3 move = boss->GetMove();

			move.x += sinf(angle) * boss->GetSpeed();
			move.z += cosf(angle) * boss->GetSpeed();
			//�e�N���X����rot���擾
			D3DXVECTOR3 rot = boss->GetRot();
			rot.y = angle + D3DX_PI;
			//rot����
			boss->SetRot(rot);
			//�ړ��ʑ��
			boss->SetMove(move);
		}
		else
		{//���B���Ă�����
			m_isMove = false;

			D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
			boss->SetMove(move);

			//���̈ړ���̒��I
			PickNextMovePoint(pMovePoint);
		}
	}
	else if (!m_isMove)
	{//�����Ȃ���ԂȂ�
		//�w��t���[�����~�܂�
		StopCnt();
	}
}

//=============================================
//�w��t���[�����~�܂�
//=============================================
void CBossWandering::StopCnt()
{
	++m_StopCnt;
	if (m_StopCnt > STOP_FRAME)
	{
		m_StopCnt = 0;
		m_isMove = true;
	}
}

//=============================================
//���̈ړ���̒��I
//=============================================
void CBossWandering::PickNextMovePoint(CMovePoint* pMovePoint)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, pMovePoint->GetNumPoint());
	//�����_���ňʒu�w��
  	m_MoveIdx = number(random);
	if (m_MoveIdx >= pMovePoint->GetNumPoint())
	{
		m_MoveIdx = 0;
	}
}

//=============================================
//�v���C���[�̃f�o�b�O�\��
//=============================================
void CBossWandering::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n[�{�X�i�ވʒu]%d"
		,m_MoveIdx );
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
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
void CBossChase::Chase(CBossEnemy* boss, CObject* obj)
{
	CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(obj);

	//�v���C���[�̈ʒu�ւ̕������
	D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

	// �ړI�n�Ƃ̋������v�Z
	float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

	// ���B����p��臒l
	const float threshold = 200.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ��� ���������킾����߂Â������Ȃ��悤�ɒ���

	if (distance < boss->LOST_PLAYER_DISTANCE)
	{
		//�v���C���[�Ɍ������ē�����
		MovetoPlayer(distance, threshold, Vector, boss);
	}
	else
	{
		boss->ChangeState(new CWanderingState);
	}
	
}

//=============================================
//�v���C���[�Ɍ������ē�����
//=============================================
void CBossChase::MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss)
{
	// �܂��ړI�n�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ��������s��
	if (distance > threshold)
	{
		//�Ώە��Ƃ̊p�x�v�Z
		float angle = atan2f(Vector.x, Vector.z);

		D3DXVECTOR3 move = boss->GetMove();

		move.x += sinf(angle) * boss->GetSpeed();
		move.z += cosf(angle) * boss->GetSpeed();
		//�e�N���X����rot���擾
		D3DXVECTOR3 rot = boss->GetRot();
		rot.y = angle + D3DX_PI;
		//rot����
		boss->SetRot(rot);
		//�ړ��ʑ��
		boss->SetMove(move);
	}
	else
	{//���B���Ă�����
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
		boss->SetMove(move);
	}
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

}

//=============================================
//�{�X�̃|�C���^�[�������ɂ��ăI�[�o�[���[�h
//=============================================
void CBossAttack::Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CBossEnemy* boss)
{
	CEnemyAttack::Attack(Allegiance, type, boss);
}
