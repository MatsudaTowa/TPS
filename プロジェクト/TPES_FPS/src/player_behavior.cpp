//=============================================
//
//�v���C���[�̃X�g���e�W�[�p�^�[��[player_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_behavior.h"

//=============================================
//�R���X�g���N�^
//=============================================
CPlayerMove::CPlayerMove()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerMove::~CPlayerMove()
{
}

//=============================================
//�ړ�����(�v���C���[)
//=============================================
void CPlayerMove::Move(CCharacter* character)
{
}

//=============================================
//�R���X�g���N�^
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//�U������(�v���C���[)
//=============================================
void CPlayerAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	character->SetMove(character->GetMove() * MOVE_SUBTRACTION);

	CPlayer::Motion_Type Motion;
	Motion = CPlayer::Motion_Type::MOTION_ATTACK;
	//���[�V�������
	character->SetMotion(Motion);

	CGun* gun = character->GetGun();

	int nRateCnt = gun->GetRateCnt();

	if (pMouse->GetPress(0))
	{//�ˌ��{�^���������ꂽ��
		if (character->GetGunAttack() != nullptr)
		{
			if (gun->GetAmmo() > INT_ZERO)
			{
				++nRateCnt;

				ShotBullet(character, pCamera, Allegiance, nRateCnt);
			}
			else
			{
				gun->m_pReload->Reload(gun);
			}
		}
	}
	if (pMouse->GetRelease(0))
	{
		nRateCnt = CAssultRifle::DEFAULT_AR_FIRE_RATE;
	}
	gun->SetRateCnt(nRateCnt);
}

//=============================================
//�e����
//=============================================
void CPlayerAttack::ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, int& nRateCnt)
{
	CGun* gun = character->GetGun();
	if (nRateCnt >= gun->GetFireRate())
	{
		nRateCnt = INT_ZERO;

		//�e���甭��
		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI) * 45.0f,
			character->m_apModel[14]->GetMtxWorld()._42 + 5.0f, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI) * 45.0f);

		//�ړ��ʐݒ�
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -gun->GetBulletSpeed(),
			sinf(pCamera->GetRot().x + D3DX_PI) * gun->GetBulletSpeed(),
			cosf(pCamera->GetRot().y + D3DX_PI) * -gun->GetBulletSpeed());
		//�e����
		gun->m_pShot->Shot(ShotPos, ShotMove, gun->GetSize(), gun->GetDamage(), Allegiance, gun);

		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	}

	gun->SetRateCnt(nRateCnt);
}

//=============================================
//�R���X�g���N�^
//=============================================
CPlayerAvoidance::CPlayerAvoidance()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerAvoidance::~CPlayerAvoidance()
{
}

//=============================================
//����A�N�V����
//=============================================
void CPlayerAvoidance::Avoidance(CCharacter* character)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	//�ړ��̕����̒P�ʃx�N�g���ϐ�
	D3DXVECTOR3 vecDirection(VEC3_RESET_ZERO);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += FLOAT_ONE;
	}
	else
	{
		vecDirection.z -= FLOAT_ONE;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	D3DXVECTOR3 move = character->GetMove();

	move.x += sinf(rotMoveY) * character->GetSpeed() * PLAYER_AVOIDANCE_SPEED;
	move.z += cosf(rotMoveY) * character->GetSpeed() * PLAYER_AVOIDANCE_SPEED;
	
	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rot����
	character->SetRot(rot);
	//�ړ��ʑ��
	character->SetMove(move);
}
