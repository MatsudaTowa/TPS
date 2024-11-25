//=============================================
//
//�v���C���[����[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include"renderer.h"
#include "scene.h"

//���f���p�X
const char* CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 0.7;

//�ړ���R
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CPlayer::DEFAULT_JUMP = 30.0f;

//�W�����v��
const int CPlayer::MAX_JUMPCNT = 2;

//�X�e�[�g�؂�ւ��t���[��
const int CPlayer::STATE_FRAME = 60;

//�v���C���[�����X�|�[���������W
const float CPlayer::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;

bool CPlayer::m_PlayerDeath = false;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority)
{//�C�j�V�����C�U�[�Ŋe�����o�ϐ�������

	//�X�e�[�g��ʏ��
	SetState(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL);

	//����łȂ���Ԃ�
	m_PlayerDeath = false;

}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();


	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//���[�u�l���
	SetMove(move);

	return S_OK;
}

//=============================================
//������(�Z�b�g�p)
//=============================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	SetPos(pos); //pos�ݒ�
	SetRot(rot); //rot�ݒ�
	SetLife(nLife); //�̗͑��

	//x�t�@�C���ǂݍ���
	BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�V�[���̃|�C���^�擾
	CScene* pScene = CManager::GetInstance()->GetScene();

	//CScene::MODE mode = pScene->GetSceneMode();

	//���[�u�l���
	SetMove(move);

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CObjectX::Uninit();

}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	//SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

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

			if (nStateCnt >= STATE_FRAME)
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

		//�d�͏���
		Gravity();

		//�ړ�����
		PlayerMove();
		
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
		CInputMouse* pMouse = CManager::GetInstance()->GetMouse();
		CInputPad* pPad = CManager::GetInstance()->GetPad();

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();
	}
}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	//�e�N���X�̕`����Ă�
	CCharacter::Draw();

	DebugPos();
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer* pPlayer = new CPlayer;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //rot�ݒ�
	pPlayer->SetLife(nLife); //�̗͑��

	//x�t�@�C���ǂݍ���
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	pPlayer->Init(); //����������
	
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

	if (nLife > 0)
	{//HP���c���Ă���

		nLife -= nDamage;

		//�_���[�W��ԂɕύX
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//���݂̏�Ԃ���
		SetState(state);

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//�I��
		Uninit();
		//���񂾏�Ԃ�
		m_PlayerDeath = true;
	}
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-900.0f, 0.5f, 0.0f);

	//pos���
	SetPos(PlayerPos);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetPad();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	switch (pCameraType)
	{//�T�C�h�r���[�̎��͉��ɂ��������Ȃ��悤�ɐݒ�
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
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
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

		//��Ԃ��擾
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		}
		else
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		}

		rot.y = rotMoveY + D3DX_PI;
		//rot����
		SetRot(rot);
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
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

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif // _DEBUG


}


