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
const float CPlayer_test::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CPlayer_test::DEFAULT_JUMP = 25.0f;

//�W�����v��
const int CPlayer_test::MAX_JUMPCNT = 2;

//�v���C���[�����X�|�[���������W
const float CPlayer_test::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer_test::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer_test::m_pMesh = nullptr;

DWORD CPlayer_test::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0)
, m_Motion()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������

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

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetModel();
	}

	//�p�[�c���ݒ�
	SetNumParts(NUM_PARTS);

	//���[�u�l���
	SetMove(move);

	//�p�[�c�ǂݍ���
	Load_Parts("data\\Motion.txt",NUM_PARTS);

	m_Motion = CPlayer_test::Motion_Type::MOTION_MAX; //�j���[�g�����ɐݒ�

	SetMotion(MOTION_NEUTRAL, NUM_PARTS);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPlayer_test::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CObjectX::Uninit();

}

//=============================================
//�X�V
//=============================================
void CPlayer_test::Update()
{
	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

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

		//�d�͏���
		Gravity();

		if (GetFinish())
		{
			//�ړ�����
			PlayerMove();
		}

		//�ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		//�ߋ��̈ʒu
		D3DXVECTOR3 oldpos = GetOldPos();

		//�ړ��ʎ擾
		D3DXVECTOR3 move = GetMove();

		//�ړ��ʂ��X�V(�����j
		move *= 1.0f - DAMPING_COEFFICIENT;

		//�ړ��ʑ��
		SetMove(move);

		//�ߋ��̈ʒu�ɍ��̈ʒu����
		oldpos = pos;

		//�ߋ��̈ʒu���
		SetOldPos(oldpos);

		//�ړ��ʒǉ�
		pos += move;

		//���W���X�V
		SetPos(pos);

		//�ő�ŏ��l�擾
		D3DXVECTOR3 minpos = GetMinPos();
		D3DXVECTOR3 maxpos = GetMaxPos();

		//�u���b�N�Ƃ̐ڐG����
		HitBlock();

		//���Ƃ̐ڐG����
		HitField();

		//�Q�[���̏�Ԏ擾
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetLaunding())
		{//���n���Ă�Ȃ�
			//�W�����v�����Z�b�g
			m_nJumpCnt = 0;
		}

		if (pos.y < DEADZONE_Y)
		{//���X�|�[������
			ReSpawn();
		}

		//�}�E�X�̏��擾
		CInputMouse* pMouse = CManager::GetMouse();
		CInputPad* pPad = CManager::GetPad();

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
	}
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer_test::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos���
	SetPos(PlayerPos);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer_test::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

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
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//�ǂ��������Ă邩���
	SetWay(bWay);

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		move.x = 0.0f;
		move.z = 0.0f;
		SetMotion(MOTION_NEUTRAL,NUM_PARTS); //���݂̃��[�V������ݒ�
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.y = rotMoveY + D3DX_PI;
		//rot����
		SetRot(rot);
		SetMotion(MOTION_MOVE,NUM_PARTS); //���݂̃��[�V������ݒ�
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //��
			m_nJumpCnt++; //�W�����v�����Z
		}
	}

	//�ړ��ʑ��
	SetMove(move);

	//���n���Ă邩���
	SetLanding(bLanding);

	if (pKeyboard->GetTrigger(DIK_LCONTROL))
	{
		SetMotion(MOTION_ATTACK, NUM_PARTS); //���݂̃��[�V������ݒ�
	}

}

//=============================================
//�v���C���[�̃f�o�b�O�\��
//=============================================
void CPlayer_test::DebugPos()
{
	LPD3DXFONT pFont = CManager::GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
