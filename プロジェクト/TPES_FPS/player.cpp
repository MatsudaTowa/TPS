//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"
#include "camera_state.h"

//�X�|�[���ʒu
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//�X�|�[������
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f};

//�����蔻�薳���t���[����
const int CPlayer::IGNORE_COLLISION_FRAME = 150;

//�X���[�N�����t���[����
const int CPlayer::SMOKE_RECAST_FRAME = 900;

//�ʏ�̈ړ���R
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//�v���C���[�����X�|�[���������W
const float CPlayer::DEADZONE_Y = -100.0f;

//�e�̃T�C�Y
const D3DXVECTOR3 CPlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//�X�^�~�i�̃T�C�Y
const D3DXVECTOR3 CPlayer::STAMINA_GAUGE_SIZE = { 5.0f,20.0f,0.0f };

CAmmo_UI* CPlayer::m_pAmmoUI = nullptr;
CLife_UI* CPlayer::m_pLifeUI = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority) :CCharacter(nPriority),
m_Raticle(),				//���e�B�N���̃|�C���^������
m_IgnoreColisionCnt(0),		//�����蔻�薳���J�E���g���Z�b�g
m_SmokeRecastCnt(0),		//�X���[�N�����J�E���g���Z�b�g
m_DeathCnt(0),				//���S�J�E���g���Z�b�g
m_Stamina(0),				//�X�^�~�i
m_isRelorad(false),			//�����[�h���Ă��Ȃ���Ԃ�
m_isSmoke(false),			//�X���[�N���g���Ă��Ȃ���Ԃ�
m_isEnemyColision(true),	//�G�l�~�[�Ɣ�����Ƃ��Ԃ�
m_pHitCameraEffect(),		//�J�����̃G�t�F�N�g�̃|�C���^������
m_pGunIcon(),				//�e�̃A�C�R���̃|�C���^������
m_pUlt(),					//�E���g�̃|�C���^������ 
m_pPlayerState(),			//�v���C���[�̃X�e�[�g������
m_pUltUI(),					//�E���g��UI������
m_pSmokeUI(),				//�X���[�N��UI������
m_pBlinkUI(),				//�u�����N��UI������
m_pStaminaGauge()			//�X�^�~�i�̃Q�[�W������
{//�C�j�V�����C�U�[�Ń����o�ϐ�������
	if (m_pSliding == nullptr)
	{
		m_pSliding = new CPlayerSliding;
	}
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
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
	}
}

//=============================================
//������
//=============================================
HRESULT CPlayer::Init()
{
	CCharacter::Init();

	//�X�^���t���[�������
	SetStanFrame(STAN_FRAME);

	//�X�^�~�i������
	m_Stamina = PLAYER_STAMINA;

	if (m_pPlayerState == nullptr)
	{
		m_pPlayerState = new CDefaultState;
	}

	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->SetReloadFrame(DEFAULT_AR_RELOAD_FRAME);
		m_pGun->SetDamage(DEFAULT_AR_DAMAGE);

		m_pGun->Init();
	}

	if (m_pUlt == nullptr)
	{
		m_pUlt = new CMediumUlt;
		m_pUlt->Init();
	}

	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;

	//�J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	//���݂̃V�[�����擾 TODO:�V�[���Q�Ƃ����
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		if (m_pGunIcon == nullptr)
		{
			m_pGunIcon = CGunIcon::Create({ 1150.0f, 665.0f, 0.0f }, { 70.0f,30.0f }, { 1.0f,1.0f,1.0f,1.0f }, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
		}

		if (m_pStaminaGauge == nullptr)
		{
			m_pStaminaGauge = CGauge_3D::Create(D3DXVECTOR3(pCamera->GetPosR().x + 20.0f + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 80.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),
				STAMINA_GAUGE_SIZE, CGauge_3D::GAUGE_TYPE_STAMINA, { 1.0f,1.0f,0.0f,1.0f });
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

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetInstance()->GetModel();
	}

	pCamera->SetRot({0.0f,0.0f,0.0f});

	//���[�u�l���
	SetMove(move);

	//�������[�V�����ݒ�
	SetMotion(MOTION_NEUTRAL);

	//�e�̃T�C�Y�ݒ�
	SetShadowSize(SHADOW_SIZE);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
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
	if (m_pUltUI != nullptr)
	{
		m_pStaminaGauge->Uninit();
		m_pStaminaGauge = nullptr;
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
	if (m_pSliding != nullptr)
	{
		delete m_pSliding;
		m_pSliding = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_Raticle != nullptr)
	{
		m_Raticle->Uninit();
		m_Raticle = nullptr;
	}

	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

	CCharacter::Update();

	//�_���[�W�X�e�[�g�̐؂�ւ�TODO:������X�e�[�g�p�^�[����
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

		if (m_pHitCameraEffect->GetAlpha() < 0.0f)
		{
			m_pHitCameraEffect->Uninit();
			m_pHitCameraEffect = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}

	if (!m_isBlown)
	{//������΂���Ԃ���Ȃ����
	//���͏���
		//Input();
	}
	else if (m_isBlown)
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

	if (pScene != CScene::MODE::MODE_TITLE)
	{
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
				m_SmokeRecastCnt = 0;
				m_isSmoke = false;
			}
		}

		if (m_Stamina < PLAYER_STAMINA)
		{//�X�^�~�i�������Ă���

			++m_StaminaRecoveryCnt;
			if (m_StaminaRecoveryCnt >= STAMINA_RECOVERY_FRAME)
			{//�J�E���g�����B������

				//�J�E���g���Z�b�g
				m_StaminaRecoveryCnt = 0;

				//�X�^�~�i��
				m_Stamina += STAMINA_RECOVERY;

				int nStaminaPer = m_Stamina % AVOIDANCE_COST;
				if (nStaminaPer == 0)
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

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 16.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Raticle->Update();
		}

		if (m_isRelorad)
		{//�����[�h����������
			m_isRelorad = m_pGun->Reload(); //�����[�h���I�������false���Ԃ��Ă���
		}

		Motion(NUM_PARTS); //���[�V��������
	}

	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//UI�ݒ�
//=============================================
void CPlayer::SetUI()
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
void CPlayer::CanDetectEnemyCollision()
{
	if (m_isEnemyColision)
	{//�G�Ƃ̓����蔻����Ƃ��Ԃ�������
		ColisionEnemy();
	}
	else if (!m_isEnemyColision)
	{//�G�Ƃ̓����蔻����Ƃ�Ȃ���Ԃ�������
		++m_IgnoreColisionCnt;

		if (m_IgnoreColisionCnt > IGNORE_COLLISION_FRAME)
		{//�t���[���ɓ��B������
		 //�����蔻����Ƃ��Ԃ�
			m_IgnoreColisionCnt = 0;
			m_isEnemyColision = true;
		}
	}
}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// ��r�Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// �X�e���V���}�X�N���w�肷��
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// �X�e���V����r�֐����w�肷��
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// �X�e���V�����ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// Z�e�X�g�E�X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g�E�X�e���V���e�X�g���s
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�e�X�g���s�E�X�e���V���e�X�g����

	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw();
	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//�v���C���[�̃f�o�b�O�\��
	DebugPos();
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer* pPlayer = new CPlayer;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //rot�ݒ�
	pPlayer->SetLife(nLife); //�̗͑��

		//�p�[�c�ǂݍ���
	pPlayer->Load_Parts("data\\motion_soldier.txt");

	pPlayer->Init(); //����������

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	return pPlayer;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CPlayer::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��ԈȊO��HP���c���Ă���

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= CPlayer::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= CPlayer::PLAYER_LIFE * 0.3f && nLife < CPlayer::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < CPlayer::PLAYER_LIFE * 0.3f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::SEVERE);
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
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//���X�|�[��
		ReSpawn();
	}
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	//�X�|�[�����̐ݒ�ɂ��ǂ�
	SetPos(CPlayer::PLAYER_SPAWN_POS);
	SetMove({0.0f,0.0f,0.0f});
	SetBlown(false);
	SetRot(CPlayer::PLAYER_SPAWN_ROT);
	SetLife(CPlayer::PLAYER_LIFE);
	SetStamina(CPlayer::PLAYER_STAMINA);
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;
	m_StaminaRecoveryCnt = 0;
	m_isSmoke = true; //�X���[�N���g������Ԃɂ����񂾎��̃f�����b�g��
	m_SmokeRecastCnt = 0;
	//TODO:�L�������Ⴄ�ꍇ�͎q�N���X�Ŏ���
	m_pGun->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
	ChangePlayerState(new CDefaultState);

	++m_DeathCnt;
}

//=============================================
//�ړ�����
//=============================================
void CPlayer::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//�ړ��̕����̒P�ʃx�N�g���ϐ�
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	CPlayer::Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		Motion = CPlayer::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CPlayer::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
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

			if (m_Stamina <= 0)
			{//�X�^�~�i��0�����������
				m_Stamina = 0;
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

		if (m_Raticle == nullptr)
		{//�g���Ă��Ȃ�������
			m_Raticle = new CReticle;

			//�l����
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Raticle->SetSize({5.0f,5.0f,0.0f});

			m_Raticle->Init();
		}
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, this);
	}

	if (pMouse->GetRelease(1))
	{//�}�E�X�������ꂽ��
		//�ړ���ԂɕύX
		ChangeState(new CMoveState);

		if(m_Raticle != nullptr)
		{//�g���Ă�����
			m_Raticle->Uninit();
			m_Raticle = nullptr;
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
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + 50.0f,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -20.0f,
					sinf(pCamera->GetRot().x + D3DX_PI) * 20.0f,
					cosf(pCamera->GetRot().y + D3DX_PI) * -20.0f }, { 0.0f,0.0f,0.0f });
		}
	}
}

//=============================================
//�v���C���[�̃X�e�[�g�ύX
//=============================================
void CPlayer::ChangePlayerState(CPlayerState* state)
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
void CPlayer::ResetRot()
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
void CPlayer::ColisionEnemy()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
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
void CPlayer::ChangeDamageState()
{
	// ��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		nStateCnt++;

		if (nStateCnt >= 30)
		{
			//�ʏ�ɖ߂�
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//�X�e�[�g�J�E���g���Z�b�g
			nStateCnt = 0;

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
void CPlayer::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nEnemyPartsCnt = 0; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
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
void CPlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n�e��:%d\n�̗�:%d\n�X�^�~�i:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(),GetLife(),GetStamina());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
