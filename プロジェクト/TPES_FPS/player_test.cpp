//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_test.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"

//�X�|�[���ʒu
const D3DXVECTOR3 CPlayer_test::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//�X�|�[������
const D3DXVECTOR3 CPlayer_test::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f};

//�ʏ�̈ړ����x
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//�v���C���[�����X�|�[���������W
const float CPlayer_test::DEADZONE_Y = -100.0f;

CAmmo_UI* CPlayer_test::m_pAmmoUI = nullptr;
CLife_UI* CPlayer_test::m_pLifeUI = nullptr;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority),m_Raticle(), m_bSmoke(), m_pHitCameraEffect()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������
	if (m_pSliding == nullptr)
	{
		m_pSliding = new CPlayerSliding;
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
CPlayer_test::~CPlayer_test()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayer_test::Init()
{
	CCharacter::Init();

	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	//���݂̃V�[�����擾 TODO:�V�[���Q�Ƃ����
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//�c�e��������
		if (m_pAmmoUI == nullptr)
		{
			m_pAmmoUI = new CAmmo_UI;

			m_pAmmoUI->Init();
		}
		//�̗�UI������
		if (m_pLifeUI == nullptr)
		{
			m_pLifeUI = new CLife_UI;

			m_pLifeUI->Init();
		}
	}

	m_pHitCameraEffect = nullptr;

	m_Raticle = nullptr;

	m_bSmoke = false;

	m_bRelorad = false;

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetInstance()->GetModel();
	}

	//�J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	pCamera->SetRot({0.0f,0.0f,0.0f});

	//���[�u�l���
	SetMove(move);

	//�p�[�c�ǂݍ���
	Load_Parts("data\\motion_soldier.txt");

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPlayer_test::Uninit()
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
	if (m_pSliding != nullptr)
	{
		delete m_pSliding;
		m_pSliding = nullptr;
	}

	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer_test::Update()
{
	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

	//�_���[�W�X�e�[�g�̐؂�ւ�TODO:������X�e�[�g�p�^�[����
	ChangeDamageState();

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
	CCharacter::Update();
	ColisionEnemy();

	if (m_bRelorad == true)
	{//�����[�h����������
		m_bRelorad = m_pGun->Reload(); //�����[�h���I�������false���Ԃ��Ă���
	}

	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetAmmo_UI(m_pGun->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
	}

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

		if (GetFinish())
		{
			//���͏���
			Input();

			if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
			{
				m_pSliding->Sliding(this);
			}
			else
			{
				m_pCharacterState->Move(this);
			}
		}

		//�J�������擾
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		}

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();

		Motion(NUM_PARTS); //���[�V��������
	}

	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//�`��
//=============================================
void CPlayer_test::Draw()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse() ;
	pMouse->Debug();
	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw();
	//�v���C���[�̃f�o�b�O�\��
	DebugPos();
}

//=============================================
//����
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer_test* pPlayer = new CPlayer_test;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //rot�ݒ�
	pPlayer->SetLife(nLife); //�̗͑��

	pPlayer->Init(); //����������

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	return pPlayer;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CPlayer_test::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��ԈȊO��HP���c���Ă���

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= CPlayer_test::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= CPlayer_test::PLAYER_LIFE * 0.3f && nLife < CPlayer_test::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < CPlayer_test::PLAYER_LIFE * 0.3f)
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
void CPlayer_test::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	//�X�|�[�����̐ݒ�ɂ��ǂ�
	SetPos(CPlayer_test::PLAYER_SPAWN_POS);
	SetRot(CPlayer_test::PLAYER_SPAWN_ROT);
	SetLife(CPlayer_test::PLAYER_LIFE);
	//TODO:�L�������Ⴄ�ꍇ�͎q�N���X�Ŏ���
	m_pGun->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer_test::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pMouse->GetPress(1))
	{//�}�E�X��������Ă�Ԃ�
		//�ˌ���ԂɕύX
		ChangeState(new CShotState);

		//���[�V������ύX TODO:�`�����ރ��[�V������
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //���e�B�N���̂ق������������̂�

		if (m_Raticle == nullptr)
		{//�g���Ă��Ȃ�������
			m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
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

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//�����[�h
			m_bRelorad = true;
		}
	}

	if (!m_bSmoke)
	{
		if (pKeyboard->GetTrigger(DIK_Q))
		{
			m_bSmoke = true;
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + 50.0f,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -10.0f,
					sinf(pCamera->GetRot().x + D3DX_PI) * 10.0f,
					cosf(pCamera->GetRot().y + D3DX_PI) * -10.0f }, { 0.0f,0.0f,0.0f });
		}
	}
}

//=============================================
//�v���C���[�̕������J�����̂ق���
//=============================================
void CPlayer_test::ResetRot()
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
void CPlayer_test::ColisionEnemy()
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

void CPlayer_test::ChangeDamageState()
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

void CPlayer_test::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
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
void CPlayer_test::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n�e��:%d\n�̗�:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(),GetLife());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
