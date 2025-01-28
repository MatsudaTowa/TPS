//=============================================
//
//�A���e�B���b�g[ult.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult.h"
#include "ult_range.h"

//=============================================
//�R���X�g���N�^
//=============================================
CUlt::CUlt():
m_CoolTimeCnt(0),	//�J�E���g0��
m_CoolTime(0),		//�N�[���^�C��0��
m_isFinish(false)	//�I����Ă��Ȃ���Ԃ�
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CUlt::~CUlt()
{
}

//=============================================
//������
//=============================================
HRESULT CUlt::Init()
{
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CUlt::Uninit()
{
	delete this;
}

//=============================================
//�X�V
//=============================================
void CUlt::Update()
{
	if (m_CoolTimeCnt < m_CoolTime)
	{
		++m_CoolTimeCnt;
	}
	else if (m_CoolTimeCnt >= m_CoolTime)
	{//�N�[���^�C���ɓ��B������
		//�I�����ĂȂ���Ԃ�
		m_isFinish = false;
	}
}

const float CMediumUlt::FLYING_HIGHT = 400.0f;
const D3DXVECTOR3 CMediumUlt::SPEED = {14.0f,16.0f,14.0f};

//=============================================
//�R���X�g���N�^
//=============================================
CMediumUlt::CMediumUlt():m_move_y(0.0f), m_pUltRange(), m_pUltCameraEffect()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMediumUlt::~CMediumUlt()
{
}

//=============================================
//������
//=============================================
HRESULT CMediumUlt::Init()
{
	//�e�N���X�̏�����
	CUlt::Init();

	SetCoolTime(MEDIUM_ULT_COOL_TIME);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMediumUlt::Uninit()
{
	if (m_pUltRange != nullptr)
	{//�E���g�̔��肪�j������Ă��Ȃ����
		m_pUltRange->Uninit();
		m_pUltRange = nullptr;
	}

	if (m_pUltCameraEffect != nullptr)
	{//�j������Ă��Ȃ����
		m_pUltCameraEffect->Uninit();
		m_pUltCameraEffect = nullptr;
	}

	//�e�N���X�̏I��
	CUlt::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMediumUlt::Update()
{
	//�e�N���X�̍X�V
	CUlt::Update();

	if (m_pUltRange != nullptr)
	{//�E���g�̔��肪��������Ă����
		m_pUltRange->Update();
		if (m_pUltRange->GetLife() <= 0)
		{
			m_pUltRange->Uninit();
			m_pUltRange = nullptr;
		}
	}
}

//=============================================
//�E���g�̎��s����
//=============================================
bool CMediumUlt::Action(CPlayer* player)
{
	float rot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (!m_isFinish)
	{
		if (m_move_y < FLYING_HIGHT)
		{
			if (m_pUltCameraEffect == nullptr)
			{
				m_pUltCameraEffect = CUltCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f });
			}
			player->SetMove({ sinf(rot) * SPEED.x,SPEED.y,cosf(rot) * SPEED.z });
			m_move_y += SPEED.y;
		}
		if (m_move_y >= FLYING_HIGHT)
		{
			player->SetMove({ sinf(rot) * SPEED.x,-SPEED.y * 2.0f,cosf(rot) * SPEED.z });

			if (player->GetLaunding())
			{//���n������I��
				if (m_pUltRange == nullptr)
				{
					m_pUltRange = CUltRange::Create(player->GetPos());

					if (m_pUltCameraEffect != nullptr)
					{//�j������Ă��Ȃ����
						m_pUltCameraEffect->Uninit();
						m_pUltCameraEffect = nullptr;
					}
				}
				m_isFinish = true;
				m_move_y = 0;

				//�N�[���^�C�����Z�b�g
				SetCoolTimeCnt(0);
			}
		}
	}
	return m_isFinish;
}
