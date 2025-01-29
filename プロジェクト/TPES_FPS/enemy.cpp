//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "wave.h"
#include "player.h"
#include "normal_enemy.h"
#include "boss_enemy.h"

//�G�l�~�[����
int CEnemy::m_NumEnemy = 0;

//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CEnemy::DEFAULT_JUMP = 25.0f;

//�����艺�ɍs�����玀�ʍ��W
const float CEnemy::DEADZONE_Y = -100.0f;

//�X�e���V���e�X�g�L���t���[��
const int CEnemy::STENCIL_FLAME = 300.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority),m_Type(), m_isStencil(false),m_StencilCnt(0)
{//�C�j�V�����C�U�[�Ń����o�ϐ�������

	//�����ǉ�
	m_NumEnemy++;
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
	//��������
	m_NumEnemy--;
}

//=============================================
//������
//=============================================
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//�X�^���t���[�������
	SetStanFrame(STAN_FRAME);

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�u�l���
	SetMove(move);

	m_Motion = CEnemy::Motion_Type::MOTION_MAX; //�j���[�g�����ɐݒ�

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy::Update()
{
	CCharacter::Update();

	m_pCharacterState->Move(this);

	m_pCharacterState->Stan(this);

	m_pCharacterState->Confusion(this);

	m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL,this);

	if (m_isStencil)
	{//�X�e���V���e�X�g���L����������
		++m_StencilCnt;
		if (m_StencilCnt > STENCIL_FLAME)
		{//�t���[���ɓ��B���Ă�����
			m_StencilCnt = 0;
			//�X�e���V���e�X�g�𖳌���
			m_isStencil = false;
		}
	}

	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene == CScene::MODE::MODE_TITLE)
	{
		return;
	}

	//�_���[�W�X�e�[�g�̐؂�ւ�TODO:������X�e�[�g�p�^�[����
	ChangeDamageState();

	//�Q�[���̏�Ԏ擾
	CGame::GAME_STATE Game_state = CGame::GetState();

	if (GetPos().y < DEADZONE_Y)
	{//���X�|�[������
		ReSpawn();
	}
}

//=============================================
//�`��
//=============================================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, m_isStencil);
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
}

//=============================================
//����
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE::ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
		pEnemy->Load_Parts("data\\motion_enemy000.txt");
		break;
	case ENEMY_TYPE::ENEMY_TYPE_BOSS:
		pEnemy = new CBossEnemy;
		pEnemy->Load_Parts("data\\motion_boss.txt");
		break;
	default:
		assert(false);
		break;
	}

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type;
	pEnemy->SetPos(pos); //pos�ݒ�
	pEnemy->SetRot(rot); //rot�ݒ�

	pEnemy->Init(); //����������

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //�^�C�v�ݒ�

	return pEnemy;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CEnemy::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();
	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0)
	{//�_���[�W��ԈȊO��HP���c���Ă���
		nLife -= nDamage;

		if (!m_isStencil)
		{
			m_isStencil = true;
		}

		if (state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//�_���[�W��ԂɕύX
			state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

			//��ԑ��
			SetState(state);
		}

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//���݂̃V�[�����擾
		CScene::MODE pScene = CScene::GetSceneMode();

		if (pScene == CScene::MODE_GAME)
		{
			CScore* pScore = CWave::GetScore();

			int nAddScore = 0;
			//TODO:������X�g���e�W�[�ł��ׂ�
			switch (m_Type)
			{
			case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
				nAddScore = 300;
				break;
			case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
				nAddScore = 1000;
				break;
			default:
				assert(false);
				break;
			}
			pScore->AddScore(nAddScore);
		}
		
		//�I��
		Uninit();
	}
}

//=============================================
//�E���g�����������Ƃ��̏���
//=============================================
void CEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	//�E���g�̒��n�n�_�ƓG�̕������
	D3DXVECTOR3 Vector = UltPos - GetPos();

	//�Ώە��Ƃ̊p�x�v�Z
	float angle = atan2f(Vector.x, Vector.z);

	D3DXVECTOR3 move = GetMove();
	
	if (GetLaunding())
	{
		//���Ε����ɐ�����΂��̂ŃX�s�[�h�̓}�C�i�X
		move.x += sinf(angle) * (-GetSpeed() * 10.0f);
		move.y += 40.0f;
		move.z += cosf(angle) * (-GetSpeed() * 10.0f);
	}

	//�ړ��ʑ��
	SetMove(move);

	Damage(nDamage);

}

//=============================================
//�v���C���[�ƃ��C���������Ă��邩
//=============================================
CCharacter::RayHitInfo CEnemy::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info;

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
		 //�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				//���C�����_����̍��������΂�(y�̓G�l�~�[�����΂��ۂ̍�������)
				D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y,character->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer::NUM_PARTS; nCnt++)
				{
					//���C���΂��v���C���[�Ɠ����邩�`�F�b�N
					D3DXIntersect(pPlayer->m_apModel[nCnt]->GetModelInfo(nCnt).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
					if (Info.hit == true)
					{
						return Info;
					}
				}
			}
		}
	}
	return Info;
}

//=============================================
//���X�|�[��
//=============================================
void CEnemy::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 EnemyPos = GetPos();

	EnemyPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos���
	SetPos(EnemyPos);
}

//=============================================
//�_���[�W�X�e�[�g�̐؂�ւ�
//=============================================
void CEnemy::ChangeDamageState()
{
	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		nStateCnt++;

		if (nStateCnt >= 10)
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