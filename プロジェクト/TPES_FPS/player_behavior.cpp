//=============================================
//
//�v���C���[�̃X�g���e�W�[�p�^�[��[player_behavior.cpp]
//Auther Matsuda Towa
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
CPlayerSliding::CPlayerSliding()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayerSliding::~CPlayerSliding()
{
}

//=============================================
//�X���C�f�B���O
//=============================================
void CPlayerSliding::Sliding(CPlayer* player)
{
	//�X�s�[�h������Ό���
	//if (move.x > 0.0f)
	//{
	//	move.x -= 0.001f;
	//}
	//else if (move.x < 0.0f)
	//{
	//	move.x += 0.001f;
	//}
	//if (move.z > 0.0f)
	//{
	//	move.z -= 0.001f;
	//}
	//else if (move.z < 0.0f)
	//{
	//	move.z += 0.001f;
	//}
	//player->SetMove(move);
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
void CPlayerAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	character->SetMove(character->GetMove() * 0.75f);

	CPlayer::Motion_Type Motion;
	Motion = CPlayer::Motion_Type::MOTION_ATTACK;
	//���[�V�������
	character->SetMotion(Motion);

	if (pMouse->GetPress(0))
	{//�ˌ��{�^���������ꂽ��
		if (character->m_pGunAttack != nullptr)
		{
			if (character->m_pGun->GetAmmo() > 0)
			{
				++character->m_pGun->m_nRateCnt;

				ShotBullet(character, pCamera, Allegiance, type);
			}
			else
			{
				character->m_pGun->m_pReload->Reload(character->m_pGun);
			}
		}
	}
	if (pMouse->GetRelease(0))
	{
		character->m_pGun->m_nRateCnt = CAssultRifle::DEFAULT_AR_FIRE_RATE;
	}
}

//=============================================
//�e����
//=============================================
void CPlayerAttack::ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type)
{
	if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
	{
		character->m_pGun->m_nRateCnt = 0;
		//�e���甭�� TODO:�e���ƕ�������������

		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI) * 45.0f,
			character->m_apModel[14]->GetMtxWorld()._42 + 5.0f, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI) * 45.0f);

		//�ړ��ʐݒ�
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed(),
			sinf(pCamera->GetRot().x + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
			cosf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed());
		//�e����
		character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->GetDamage(), Allegiance, type, character->m_pGun);

		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	}
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
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}
	else
	{
		vecDirection.z -= 1.0f;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	D3DXVECTOR3 move = character->GetMove();

	move.x += sinf(rotMoveY) * character->GetSpeed() * 30.0f;
	move.z += cosf(rotMoveY) * character->GetSpeed() * 30.0f;
	
	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rot����
	character->SetRot(rot);
	//�ړ��ʑ��
	character->SetMove(move);
}
