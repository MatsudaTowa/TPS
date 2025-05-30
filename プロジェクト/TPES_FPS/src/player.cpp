//=============================================
//
//�v���C���[[player.cpp]
//Author Matsuda Towa
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

//�e�̃T�C�Y
const D3DXVECTOR3 CPlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority) :CCharacter(nPriority)
{
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
	CCharacter::Init();

	SetPos(PLAYER_SPAWN_POS); //pos�ݒ�
	SetRot(PLAYER_SPAWN_ROT); //rot�ݒ�

	//�J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = VEC3_RESET_ZERO;

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
//�I��
//=============================================
void CPlayer::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	CCharacter::Update();

	for (int nCnt = 0; nCnt < GetNumParts(); nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}

	Motion(GetNumParts()); //���[�V��������
	//CCharacter::HitBlock(NUM_PARTS);
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
CPlayer* CPlayer::Create(CPlayer* player)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer* pPlayer = player;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) { return nullptr; }

		//�p�[�c�ǂݍ���
	pPlayer->Load_Parts("data\\motion_soldier.bin");

	pPlayer->Init(); //����������

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	return pPlayer;
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

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
