//=============================================
//
//�Q�[�W�Ǘ�[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge.h"

//=============================================
//�R���X�g���N�^
//=============================================
CGauge::CGauge(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge::Init()
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
void CGauge::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();

	//���_�ݒ�
	SetGaugeVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CGauge::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}


//=============================================
//�Q�[�W�ݒ�
//=============================================
void CGauge::SetGauge(D3DXVECTOR2 size)
{
	SetSize(size);
}

//=============================================
//����
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col)
{
	CGauge* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
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
CGauge_Life::CGauge_Life(int nPriority) :CGauge(nPriority)
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
	CGauge::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Life::Uninit()
{
	//�e�N���X�̏I��
	CGauge::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Life::Update()
{
	//�e�N���X�̍X�V
	CGauge::Update();
}

//=============================================
//�`��
//=============================================
void CGauge_Life::Draw()
{
	//�e�N���X�̕`��
	CGauge::Draw();
}

