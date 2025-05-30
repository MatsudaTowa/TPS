//=============================================
//
//�������v���C���[[active_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_player.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"
#include "camera_state.h"

//�X�|�[���ʒu
const D3DXVECTOR3 CActivePlayer::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//�X�|�[������
const D3DXVECTOR3 CActivePlayer::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f };

//�e�̃T�C�Y
const D3DXVECTOR3 CActivePlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//�e��UI�̈ʒu
const D3DXVECTOR3 CActivePlayer::GUN_UI_POS = { 1150.0f, 665.0f, 0.0f };

//�e��UI�̃T�C�Y
const D3DXVECTOR2 CActivePlayer::GUN_UI_SIZE = { 70.0f,30.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CActivePlayer::CActivePlayer(int nPriority) :CPlayer(nPriority),
m_Reticle(),					//���e�B�N���̃|�C���^������
m_IgnoreColisionCnt(INT_ZERO),	//�����蔻�薳���J�E���g���Z�b�g
m_SmokeRecastCnt(INT_ZERO),		//�X���[�N�����J�E���g���Z�b�g
m_DeathCnt(INT_ZERO),			//���S�J�E���g���Z�b�g
m_Stamina(INT_ZERO),			//�X�^�~�i
m_isRelorad(false),				//�����[�h���Ă��Ȃ���Ԃ�
m_isSmoke(false),				//�X���[�N���g���Ă��Ȃ���Ԃ�
m_isEnemyColision(true),		//�G�l�~�[�Ɣ�����Ƃ��Ԃ�
m_pHitCameraEffect(),			//�J�����̃G�t�F�N�g�̃|�C���^������
m_pGunIcon(),					//�e�̃A�C�R���̃|�C���^������
m_pUlt(),						//�E���g�̃|�C���^������ 
m_pPlayerState(),				//�v���C���[�̃X�e�[�g������
m_pAmmoUI(),					//�c�e��UI�̏�����
m_pLifeUI(),					//�̗�UI�̏�����
m_pUltUI(),						//�E���g��UI������
m_pSmokeUI(),					//�X���[�N��UI������
m_pBlinkUI()					//�u�����N��UI������
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CActivePlayer::~CActivePlayer()
{
}

//=============================================
//������
//=============================================
HRESULT CActivePlayer::Init()
{
	CPlayer::Init();

	SetPos(PLAYER_SPAWN_POS); //pos�ݒ�
	SetRot(PLAYER_SPAWN_ROT); //rot�ݒ�
	SetLife(PLAYER_LIFE); //�̗͑��

	//�X�^���t���[�������
	SetStanFrame(STAN_FRAME);

	//�X�^�~�i������
	m_Stamina = PLAYER_STAMINA;

	if (m_pAvoidance == nullptr)
	{
		m_pAvoidance = new CPlayerAvoidance;
	}
	if (m_pMove == nullptr)
	{
		m_pMove = new CPlayerMove;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CPlayerAttack;
	}

	if (m_pPlayerState == nullptr)
	{
		m_pPlayerState = new CDefaultState;
	}

	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;
		m_pGun->Init();
	}

	if (m_pUlt == nullptr)
	{
		m_pUlt = new CMediumUlt;
		m_pUlt->Init();
	}

	//�u�����N�̉񐔎Z�o
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;

	//UI����
	CreateUI();

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = VEC3_RESET_ZERO;

	//�J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetRot(VEC3_RESET_ZERO);

	//���[�u�l���
	SetMove(move);

	//�������[�V�����ݒ�
	SetMotion(MOTION_NEUTRAL);

	//�e�̃T�C�Y�ݒ�
	SetShadowSize(SHADOW_SIZE);

	return S_OK;
}

//=============================================
//UI����
//=============================================
void CActivePlayer::CreateUI()
{
	if (m_pGunIcon == nullptr)
	{
		m_pGunIcon = CGunIcon::Create(GUN_UI_POS, GUN_UI_SIZE, COLOR_WHITE, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
	}
	//�c�e��������
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();

		m_pAmmoUI->SetDefaultAmmo_UI(m_pGun->GetAmmo());
	}
	//�̗�UI������
	if (m_pLifeUI == nullptr)
	{
		m_pLifeUI = new CLife_UI;

		m_pLifeUI->Init();
	}
	//�u�����NUI������
	if (m_pBlinkUI == nullptr)
	{
		m_pBlinkUI = new CBlink_UI;

		m_pBlinkUI->Init(this);
	}
	//�E���gUI������
	if (m_pUltUI == nullptr)
	{
		m_pUltUI = new CUlt_UI;

		m_pUltUI->Init(this);
	}

	if (m_pSmokeUI == nullptr)
	{
		m_pSmokeUI = new CSmoke_UI;
		m_pSmokeUI->Init(this);
	}

}

//=============================================
//�I��
//=============================================
void CActivePlayer::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->Uninit();
		m_pBlinkUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pUltUI->Uninit();
		m_pUltUI = nullptr;
	}
	if (m_pGunIcon != nullptr)
	{
		m_pGunIcon->Uninit();
		m_pGunIcon = nullptr;
	}
	if (m_pUlt != nullptr)
	{
		m_pUlt->Uninit();
		m_pUlt = nullptr;
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->Uninit();
		m_pSmokeUI = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_Reticle != nullptr)
	{
		m_Reticle->Uninit();
		m_Reticle = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
	}

	//�e�N���X�̏I���������Ă�
	CPlayer::Uninit();
}

//=============================================
//�X�V
//=============================================
void CActivePlayer::Update()
{
	CPlayer::Update();

	//�_���[�W�X�e�[�g�̐؂�ւ�
	ChangeDamageState();

	if (m_pPlayerState != nullptr)
	{
		m_pPlayerState->Default(this);
		m_pPlayerState->Ult(this);
		m_pPlayerState->Blown(this);
	}

	if (m_pHitCameraEffect != nullptr)
	{//�g���Ă�����
		m_pHitCameraEffect->SubAlpha();

		if (m_pHitCameraEffect->GetAlpha() < FLOAT_ZERO)
		{
			m_pHitCameraEffect->Uninit();
			m_pHitCameraEffect = nullptr;
		}
	}

	if (m_isBlown)
	{
		if (GetLaunding())
		{//���n������
			//�X�^����Ԃ�
			m_isBlown = false;
		}
	}

	//�G�Ɣ�����Ƃ�ꍇ��������Ƃ�
	//�Ƃ�Ȃ��ꍇ�̓J�E���g�A�b�v
	CanDetectEnemyCollision();

	//UI�ݒ�
	SetUI();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		++nStateCnt;

		//�X�e�[�g�J�E���g���
		SetStateCnt(nStateCnt);
	}

	if (m_isSmoke)
	{//�X���[�N���g������Ԃ�������
		++m_SmokeRecastCnt;
		if (m_SmokeRecastCnt > SMOKE_RECAST_FRAME)
		{
			m_SmokeRecastCnt = INT_ZERO;
			m_isSmoke = false;
		}
	}

	if (m_Stamina < PLAYER_STAMINA)
	{//�X�^�~�i�������Ă���

		++m_StaminaRecoveryCnt;
		if (m_StaminaRecoveryCnt >= STAMINA_RECOVERY_FRAME)
		{//�J�E���g�����B������

			//�J�E���g���Z�b�g
			m_StaminaRecoveryCnt = INT_ZERO;

			//�X�^�~�i��
			m_Stamina += STAMINA_RECOVERY;

			int nStaminaPer = m_Stamina % AVOIDANCE_COST;
			if (nStaminaPer == INT_ZERO)
			{
				++m_BlinkCnt;
			}

			if (m_Stamina >= PLAYER_STAMINA)
			{//�X�^�~�i���f�t�H���g�l�ɓ��B������
				//�X�^�~�i���
				m_Stamina = PLAYER_STAMINA;
			}
		}
	}

	//�J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (m_Reticle != nullptr)
	{
		m_Reticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - RETICLE_CORRECTION_VALUE, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		m_Reticle->Update();
	}

	if (m_isRelorad)
	{//�����[�h����������
		m_isRelorad = m_pGun->Reload(); //�����[�h���I�������false���Ԃ��Ă���
	}
}

//=============================================
//UI�ݒ�
//=============================================
void CActivePlayer::SetUI()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetCurrentAmmo_UI(m_pGun->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
	}

	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->SetCurrentBlink_UI(this);
	}

	if (m_pUltUI != nullptr)
	{
		m_pUltUI->SetCurrentUlt_UI(this);
	}

	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->SetCurrentSmoke_UI(this);
	}
}

//=============================================
//�G�Ƃ̔���
//=============================================
void CActivePlayer::CanDetectEnemyCollision()
{
	if (m_isEnemyColision)
	{//�G�Ƃ̓����蔻����Ƃ��Ԃ�������
		ColisionEnemy();
		return;
	}
	//�G�Ƃ̓����蔻����Ƃ�Ȃ���Ԃ�������
	++m_IgnoreColisionCnt;

	if (m_IgnoreColisionCnt > IGNORE_COLLISION_FRAME)
	{//�t���[���ɓ��B������
		//�����蔻����Ƃ��Ԃ�
		m_IgnoreColisionCnt = INT_ZERO;
		m_isEnemyColision = true;
	}
}

//=============================================
//�`��
//=============================================
void CActivePlayer::Draw()
{
	CPlayer::Draw();
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CActivePlayer::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > INT_ZERO && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��ԈȊO��HP���c���Ă���

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= PLAYER_LIFE * 0.3f && nLife < PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < PLAYER_LIFE * 0.3f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::SEVERE);
			}
		}

		nLife -= nDamage;

		//�_���[�W��ԂɕύX
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//��ԑ��
		SetState(state);

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= INT_ZERO)
	{//HP��0�ȉ���������
		//���X�|�[��
		ReSpawn();
	}
}

//=============================================
//���X�|�[��
//=============================================
void CActivePlayer::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	//�X�|�[�����̐ݒ�ɂ��ǂ�
	SetPos(CActivePlayer::PLAYER_SPAWN_POS);
	SetMove(VEC3_RESET_ZERO);
	SetBlown(false);
	SetRot(CActivePlayer::PLAYER_SPAWN_ROT);
	SetLife(CActivePlayer::PLAYER_LIFE);
	SetStamina(CActivePlayer::PLAYER_STAMINA);
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;
	m_StaminaRecoveryCnt = INT_ZERO;
	m_isSmoke = true;
	m_SmokeRecastCnt = INT_ZERO;

	m_pGun->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
	ChangePlayerState(new CDefaultState);

	++m_DeathCnt;
}

//=============================================
//�ړ�����
//=============================================
void CActivePlayer::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//�ړ��̕����̒P�ʃx�N�g���ϐ�
	D3DXVECTOR3 vecDirection(VEC3_RESET_ZERO);
	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += FLOAT_ONE;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	CPlayer::Motion_Type Motion;

	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // �����ĂȂ��B
		Motion = CPlayer::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CPlayer::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = GetMove();
	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // �����ĂȂ��B
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(rotMoveY) * GetSpeed();
		move.z += cosf(rotMoveY) * GetSpeed();
	}
	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rot����
	SetRot(rot);
	//�ړ��ʑ��
	SetMove(move);

	//���[�V�������
	SetMotion(Motion);

	if (pKeyboard->GetTrigger(DIK_LSHIFT))
	{
		if (m_Stamina >= AVOIDANCE_COST)
		{//�X�^�~�i�������
			//�u�����NSE��炷
			CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BLINK);
			m_pAvoidance->Avoidance(this);
			m_Stamina -= AVOIDANCE_COST;

			--m_BlinkCnt;

			if (m_Stamina <= INT_ZERO)
			{//�X�^�~�i��0�����������
				m_Stamina = INT_ZERO;
			}
		}
	}

	if (pKeyboard->GetPress(DIK_X))
	{
		if (m_pUlt != nullptr)
		{
			if (m_pUlt->GetCoolTimeCnt() >= m_pUlt->GetCoolTime())
			{
				pCamera->ChangeCameraState(new CUltCameraState);
				ChangePlayerState(new CUltState);
				m_pUltUI->Reset(); //UI�̃��Z�b�g����

				m_isEnemyColision = false;
			}
		}
	}

	if (pMouse->GetPress(1))
	{//�}�E�X��������Ă�Ԃ�
		//�ˌ���ԂɕύX
		ChangeState(new CShotState);

		//���[�V������ύX TODO:�`�����ރ��[�V������
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //���e�B�N���̂ق������������̂�

		if (m_Reticle == nullptr)
		{//�g���Ă��Ȃ�������
			m_Reticle = new CReticle;

			//�l����
			m_Reticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Reticle->SetSize({ 5.0f,5.0f,0.0f });

			m_Reticle->Init();
		}
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, this);
	}

	if (pMouse->GetRelease(1))
	{//�}�E�X�������ꂽ��
		//�ړ���ԂɕύX
		ChangeState(new CMoveState);

		if (m_Reticle != nullptr)
		{//�g���Ă�����
			m_Reticle->Uninit();
			m_Reticle = nullptr;
		}
	}

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//�����[�h
			m_isRelorad = true;
		}
	}

	if (!m_isSmoke)
	{
		if (pKeyboard->GetTrigger(DIK_Q))
		{
			m_isSmoke = true;
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + SMOKE_CORRECTION_VALUE,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -SMOKE_SHOT_SPEED,
					sinf(pCamera->GetRot().x + D3DX_PI) * SMOKE_SHOT_SPEED,
					cosf(pCamera->GetRot().y + D3DX_PI) * -SMOKE_SHOT_SPEED }, VEC3_RESET_ZERO);
		}
	}
}

//=============================================
//�v���C���[�̃X�e�[�g�ύX
//=============================================
void CActivePlayer::ChangePlayerState(CPlayerState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
		m_pPlayerState = state;
	}
}

//=============================================
//�v���C���[�̕������J�����̂ق���
//=============================================
void CActivePlayer::ResetRot()
{
	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y;

	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = GetRot();

	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot);
}

//=============================================
//�G�l�~�[�Ƃ̓����蔻��
//=============================================
void CActivePlayer::ColisionEnemy()
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�I�u�W�F�N�g�ɗv�f�������Ă�����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�u���b�N�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					//���S�Ƀ_�E���L���X�g
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

					CheckColisionEnemy(pEnemy, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

//=============================================
//�_���[�W��Ԃ̐؂�ւ�
//=============================================
void CActivePlayer::ChangeDamageState()
{
	// ��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		nStateCnt++;

		if (nStateCnt >= DAMAGE_FRAME)
		{
			//�ʏ�ɖ߂�
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//�X�e�[�g�J�E���g���Z�b�g
			nStateCnt = INT_ZERO;

			//��ԑ��
			SetState(state);
		}
		//�X�e�[�g�J�E���g���
		SetStateCnt(nStateCnt);
	}
}

//=============================================
//�G�Ƃ̓����蔻��
//=============================================
void CActivePlayer::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nEnemyPartsCnt = INT_ZERO; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
	{
		D3DXVECTOR3 Enemypos = { pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._41,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._42,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 EnemyMinpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMin();
		D3DXVECTOR3 EnemyMaxpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			Enemypos, EnemyMinpos, EnemyMaxpos);

		if (colision == CColision::COLISION::COLISON_X)
		{
			// X���Փˎ��̏���
			SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{
			// X���Փˎ��̏���
			SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_Z)
		{
			// X���Փˎ��̏���
			SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
		}
	}
}

//=============================================
//�v���C���[�̃f�o�b�O�\��
//=============================================
void CActivePlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n�e��:%d\n�̗�:%d\n�X�^�~�i:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(), GetLife(), GetStamina());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
