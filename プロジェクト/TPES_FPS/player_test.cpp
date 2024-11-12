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

//�ʏ�̈ړ����x
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//�W�����v��
const int CPlayer_test::MAX_JUMPCNT = 2;

//�v���C���[�����X�|�[���������W
const float CPlayer_test::DEADZONE_Y = -100.0f;

CAmmo_UI* CPlayer_test::m_pAmmoUI = nullptr;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer_test::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer_test::m_pMesh = nullptr;

DWORD CPlayer_test::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0),m_Raticle()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������
	if (m_pMove == nullptr)
	{
		m_pMove = new CDush;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CPlayerAttack;
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

	//�c�e��������
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();
	}

	m_Raticle = nullptr;

	m_bRelorad = false;

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetModel();
	}

	//�J�������擾
	CCamera* pCamera = CManager::GetCamera();

	//���[�u�l���
	SetMove(move);

	//�p�[�c�ǂݍ���
	Load_Parts("data\\Motion.txt");

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

	CCharacter::Update();

	if (m_bRelorad == true)
	{//�����[�h����������
		m_bRelorad = m_pGun->Reload(); //�����[�h���I�������false���Ԃ��Ă���
	}

	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetAmmo_UI(m_pGun->GetAmmo());
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
			nStateCnt++;

			//�X�e�[�g�J�E���g���
			SetStateCnt(nStateCnt);
		}

		if (GetFinish())
		{
			//���͏���
			Input();
		}

		//�J�������擾
		CCamera* pCamera = CManager::GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		}

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();

		Motion(NUM_PARTS); //���[�V��������
	}
}

//=============================================
//�`��
//=============================================
void CPlayer_test::Draw()
{
	CInputMouse* pMouse = CManager::GetMouse();
	pMouse->Debug();
	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw(NUM_PARTS);
	//�v���C���[�̃f�o�b�O�\��
	DebugPos();
}

//=============================================
//����
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

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

	if (nLife > 0)
	{//HP���c���Ă���
		nLife -= nDamage;

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//�I��
		Uninit();
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer_test::ReSpawn()
{
	////�������g��pos�擾
	//D3DXVECTOR3 PlayerPos = GetPos();

	//PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	////pos���
	//SetPos(PlayerPos);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer_test::Input()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputMouse* pMouse = CManager::GetMouse();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	COMBAT_STATE state = CCharacter::GetCombat_State();
	if (state != COMBAT_STATE::STATE_ATTACK)
	{
		switch (pCameraType)
		{//�T�C�h�r���[�̎��͉��ɂ��������Ȃ��悤�ɐݒ�
		case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
			if (pKeyboard->GetPress(DIK_A))
			{
				vecDirection.x -= 1.0f;
				bWay = false;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
			if (pKeyboard->GetPress(DIK_A))
			{
				vecDirection.x -= 1.0f;
				bWay = false;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		default:
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
				bWay = false;
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				vecDirection.x += 1.0f;
				bWay = true;
			}
			break;
		}
	}

	float rotMoveY = CManager::GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		Motion = MOTION_NEUTRAL;
	}
	else
	{	
		Motion = MOTION_MOVE;
	}

	//�ړ�����
	m_pMove->Move(D3DXVECTOR3(vecDirection.x, 0.0f, vecDirection.z), rotMoveY,this,Motion);

	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			//�e�N���X�̃W�����v����
			CCharacter::Jump();
			m_nJumpCnt++; //�W�����v�����Z
		}
	}

	CCharacter::COMBAT_STATE combat_state = GetCombat_State();
	CCamera* pCamera = CManager::GetCamera();
	////�ړ��ʑ��
	//SetMove(move);
	if (combat_state != CCharacter::COMBAT_STATE::STATE_ATTACK &&pMouse->GetPress(1))
	{//�A�^�b�N��Ԃ���Ȃ��}�E�X��������Ă�Ԃ�
		//�X�e�[�g���A�^�b�N��Ԃ�
		combat_state = CCharacter::COMBAT_STATE::STATE_ATTACK;

		if (m_Raticle == nullptr)
		{//�g���Ă��Ȃ�������
			m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		}
	}

	if (combat_state == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetRelease(1))
	{//�A�^�b�N��Ԃ���Ȃ��}�E�X�������ꂽ��
		//�X�e�[�g���m�[�}����Ԃ�
		combat_state = CCharacter::COMBAT_STATE::STATE_NORMAL;

		if(m_Raticle != nullptr)
		{//�g���Ă�����
			m_Raticle->Uninit();
			m_Raticle = nullptr;
		}
	}

	SetCombat_State(combat_state);

	if (GetCombat_State() == CCharacter::COMBAT_STATE::STATE_ATTACK && pMouse->GetPress(0))
	{//�A�^�b�N��Ԃ�������
		if (m_pAttack != nullptr)
		{
			m_pAttack->Attack(D3DXVECTOR3(m_Raticle->GetPos()), D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -CAssultRifle::DEFAULT_AR_BULLET_SPEED,
				sinf(pCamera->GetRot().x + D3DX_PI)* CAssultRifle::DEFAULT_AR_BULLET_SPEED,
				cosf(pCamera->GetRot().y + D3DX_PI) * -CAssultRifle::DEFAULT_AR_BULLET_SPEED),
				D3DXVECTOR3(1.5f, 1.5f, 1.5f), 1, CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, m_pGun, this);
		}
	}
	if (pMouse->GetRelease(0))
	{
		m_pGun->m_nRateCnt = 0;
	}

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//�����[�h
			m_bRelorad = true;
		}
	}
}

//=============================================
//�v���C���[�̃f�o�b�O�\��
//=============================================
void CPlayer_test::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n�e��:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
