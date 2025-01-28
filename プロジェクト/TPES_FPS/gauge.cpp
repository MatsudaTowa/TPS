//=============================================
//
//�Q�[�W�Ǘ�[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge.h"
#include "manager.h"

const std::string CGauge_2D::TEXTURE_NAME = "data\\TEXTURE\\gauge.png";

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_2D::CGauge_2D(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_2D::~CGauge_2D()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_2D::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetGaugeVtx(1.0f);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_2D::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_2D::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();

	//���_�ݒ�
	SetGaugeVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CGauge_2D::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}


//=============================================
//�Q�[�W�ݒ�
//=============================================
void CGauge_2D::SetGauge(D3DXVECTOR2 size)
{
	SetSize(size);
}

//=============================================
//����
//=============================================
CGauge_2D* CGauge_2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col)
{
	CGauge_2D* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		break;
	case GAUGE_TYPE_STAMINA:
		pGauge = new CGauge_Stamina;
		break;
	default:
		assert(false);
		break;
	}

	// null�Ȃ�null��Ԃ�
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos�ݒ�

	pGauge->SetSize(size); //size�ݒ�

	pGauge->SetColor(col);

	pGauge->m_type = type; //�Q�[�W�̃^�C�v�ݒ�

	pGauge->SetType(OBJECT_TYPE_GAUGE); //�^�C�v�ݒ�

	pGauge->Init();

	return pGauge;
}

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_3D::CGauge_3D(int nPriority) :CBillboard(nPriority),
m_type(),
m_isVisible(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_3D::~CGauge_3D()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_3D::Init()
{
	//�e�N���X�̏��������Ă�
	CBillboard::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetGaugeVtx(m_ReferencePos, {0.0f,0.0f,-1.0f});

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_3D::Uninit()
{
	//�e�N���X�̏I�����Ă�
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_3D::Update()
{
	//�e�N���X�̍X�V���Ă�
	CBillboard::Update();

	//���_�ݒ�
	SetGaugeVtx(m_ReferencePos,{ 0.0f,0.0f,-1.0f });
}

//=============================================
//�`��
//=============================================
void CGauge_3D::Draw()
{
	if (m_isVisible)
	{
		//�e�N���X�̕`����Ă�
		CBillboard::Draw();
	}
}

//=============================================
//����
//=============================================
CGauge_3D* CGauge_3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GAUGE3D_TYPE type, D3DXCOLOR col)
{
	CGauge_3D* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_STAMINA:
		//pGauge = new CGauge_Stamina;
		break;
	default:
		assert(false);
		break;
	}

	// null�Ȃ�null��Ԃ�
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos�ݒ�

	pGauge->m_ReferencePos = pos;

	pGauge->SetSize(size); //size�ݒ�

	pGauge->SetColor(col);

	pGauge->m_type = type; //�Q�[�W�̃^�C�v�ݒ�

	pGauge->SetType(OBJECT_TYPE_GAUGE); //�^�C�v�ݒ�

	pGauge->Init();

	return pGauge;
}


//=============================================
//�R���X�g���N�^
//=============================================
CGauge_Life::CGauge_Life(int nPriority) :CGauge_2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_Life::Init()
{
	//�e�N���X�̏�����
	CGauge_2D::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Life::Uninit()
{
	//�e�N���X�̏I��
	CGauge_2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Life::Update()
{
	//�e�N���X�̍X�V
	CGauge_2D::Update();
}

//=============================================
//�`��
//=============================================
void CGauge_Life::Draw()
{
	//�e�N���X�̕`��
	CGauge_2D::Draw();
}

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_Stamina::CGauge_Stamina(int nPriority):CGauge_2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_Stamina::~CGauge_Stamina()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_Stamina::Init()
{
	//�e�N���X�̏�����
	CGauge_2D::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Stamina::Uninit()
{
	//�e�N���X�̏I��
	CGauge_2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Stamina::Update()
{
	//�e�N���X�̍X�V
	CGauge_2D::Update();
}

//=============================================
//�`��
//=============================================
void CGauge_Stamina::Draw()
{
	//�e�N���X�̕`��
	CGauge_2D::Draw();
}
