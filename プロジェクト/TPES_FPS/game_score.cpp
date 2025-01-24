//=============================================
//
//�Q�[���X�R�A�����ugame_scorer.cpp�v
// Author���c�i�v
//
//=============================================
#include "game_score.h"
#include "player.h"

const float CGameScore::DIGIT_SHIFT = 40.0f;

const D3DXVECTOR3 CGameScore::BOX_POS = { 650.0f, 60.0f, 0.0f };
const D3DXVECTOR2 CGameScore::BOX_SIZE = { 400.0f, 80.0f };

const D3DXVECTOR3 CGameScore::DEATH_ICON_POS = { 750.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::DEATH_ICON_SIZE = { 50.0f, 30.0f };

const D3DXVECTOR3 CGameScore::NUM_DEATH_POS = { 845.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::NUM_DEATH_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CGameScore::SCORE_POS = { 650.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::SCORE_SIZE = { 20.0f, 30.0f };

//=============================================
//�R���X�g���N�^
//=============================================
CGameScore::CGameScore():
m_pDeathCnt(),						//���S���J�E���g�����|�C���^������
m_pPlayerUIBox(),					//UI�{�b�N�X�̃|�C���^������
m_pDeathIcon(),						//���S�A�C�R��������
m_DeathCntPos({0.0f,0.0f,0.0f})		//���S���̈ʒu
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGameScore::~CGameScore()
{
}

//=============================================
//������
//=============================================
HRESULT CGameScore::Init()
{
	//�����ʒu���
	m_DeathCntPos = NUM_DEATH_POS;
	//Ui�̘g����
	if (m_pPlayerUIBox == nullptr)
	{
		m_pPlayerUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_SCORE);
	}

	//���S�A�C�R������
	if (m_pDeathIcon == nullptr)
	{
		m_pDeathIcon = CDeathIcon::Create(DEATH_ICON_POS, DEATH_ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	for (int nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		if (m_pDeathCnt[nCnt] == nullptr)
		{
			m_pDeathCnt[nCnt] = CNumber_2D::Create(m_DeathCntPos, NUM_DEATH_SIZE);
			//���W�����炷
			m_DeathCntPos.x -= DIGIT_SHIFT;
		}
	}

	CScore::SetPos(SCORE_POS);

	CScore::SetSize(SCORE_SIZE);

	CScore::SetDigitShift(DIGIT_SHIFT);

	CScore::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGameScore::Uninit()
{
	for (int nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		if (m_pDeathCnt[nCnt] != nullptr)
		{
			m_pDeathCnt[nCnt]->Uninit();
			m_pDeathCnt[nCnt] = nullptr;
		}
	}

	if (m_pPlayerUIBox != nullptr)
	{
		m_pPlayerUIBox->Uninit();
		m_pPlayerUIBox = nullptr;
	}

	if (m_pDeathIcon != nullptr)
	{
		m_pDeathIcon->Uninit();
		m_pDeathIcon = nullptr;
	}

	CScore::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGameScore::Update()
{
	CScore::Update();

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
				CPlayer* pplayer = dynamic_cast<CPlayer*>(pObj);

				SetDeathCntUI(pplayer->GetDeathCnt());
			}
		}
	}
}

//=============================================
//���S���ݒ�
//=============================================
void CGameScore::SetDeathCntUI(int nDeathCnt)
{
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[DEATH_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = nDeathCnt / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = DEATH_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pDeathCnt[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
