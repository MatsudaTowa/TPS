//=============================================
//
//3DTemplate[enemy_test.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_test.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"

//�G�l�~�[����
int CEnemy_test::m_NumEnemy = 0;

//�ʏ�̈ړ����x
const float CEnemy_test::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CEnemy_test::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CEnemy_test::DEFAULT_JUMP = 25.0f;

//�W�����v��
const int CEnemy_test::MAX_JUMPCNT = 2;

//�v���C���[�����X�|�[���������W
const float CEnemy_test::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEnemy_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy_test::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy_test::m_pMesh = nullptr;

DWORD CEnemy_test::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_test::CEnemy_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0)
, m_Motion()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������
	//�����ǉ�
	m_NumEnemy++;
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_test::~CEnemy_test()
{
	//��������
	m_NumEnemy--;
}

//=============================================
//������
//=============================================
HRESULT CEnemy_test::Init()
{

	CCharacter::Init();

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�u�l���
	SetMove(move);

	Load_Parts("data\\Motion.txt");

	m_Motion = CEnemy_test::Motion_Type::MOTION_MAX; //�j���[�g�����ɐݒ�

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_test::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();

}

//=============================================
//�X�V
//=============================================
void CEnemy_test::Update()
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

		//�ړ�����
		Move();

		//�Q�[���̏�Ԏ擾
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetLaunding())
		{//���n���Ă�Ȃ�
			//�W�����v�����Z�b�g
			m_nJumpCnt = 0;
		}

		if (GetPos().y < DEADZONE_Y)
		{//���X�|�[������
			ReSpawn();
		}

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();

		Motion(NUM_PARTS); //���[�V��������
	}
}

//=============================================
//�`��
//=============================================
void CEnemy_test::Draw()
{
	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw(NUM_PARTS);
}

//=============================================
//����
//=============================================
CEnemy_test* CEnemy_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CEnemy_test* pEnemy = new CEnemy_test;

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->SetPos(pos); //pos�ݒ�
	pEnemy->SetRot(rot); //rot�ݒ�
	pEnemy->SetLife(nLife); //�̗͑��

	pEnemy->Init(); //����������

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //�^�C�v�ݒ�

	return pEnemy;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CEnemy_test::Damage(int nDamage)
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
void CEnemy_test::ReSpawn()
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
void CEnemy_test::Move()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

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
		SetMotion(MOTION_NEUTRAL); //���݂̃��[�V������ݒ�
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
		SetMotion(MOTION_MOVE); //���݂̃��[�V������ݒ�
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //��
			m_nJumpCnt++; //�W�����v�����Z
			SetMotion(MOTION_ATTACK); //���݂̃��[�V������ݒ�

		}
	}

	//�ړ��ʑ��
	SetMove(move);

	//���n���Ă邩���
	SetLanding(bLanding);
}