//=============================================
//
//�|�[�Y��UI[pause_select.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select.h"
#include "manager.h"

//�F
const D3DXCOLOR CPauseSelect::DEFAULT_COLOR = { 0.3f,0.3f,0.3f,1.0f };
//�T�C�Y
const D3DXVECTOR2 CPauseSelect::SIZE = { 180.0f,50.0f };

//=============================================
// �R���X�g���N�^
//=============================================
CPauseSelect::CPauseSelect(int nPriority):CObject2D(nPriority),
m_isSelect(false)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CPauseSelect::~CPauseSelect()
{
}

//=============================================
// ������
//=============================================
HRESULT CPauseSelect::Init()
{
	CObject2D::Init();
	//�T�C�Y
	SetSize(SIZE);
	//���_����
	SetVtx(FLOAT_ONE);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CPauseSelect::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CPauseSelect::Update()
{
	CObject2D::Update();
	//���_����
	SetVtx(FLOAT_ONE);
	POINT pMousePos;
	GetCursorPos(&pMousePos);
	ScreenToClient(CManager::GetInstance()->GetHWnd(), &pMousePos);

	if (!m_isSelect)
	{
		SetColor(DEFAULT_COLOR);
		return;
	}

	SetColor(COLOR_WHITE);

}

//=============================================
// �`��
//=============================================
void CPauseSelect::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CPauseSelect* CPauseSelect::Create(D3DXVECTOR3 pos, CPauseSelect* select)
{
	CPauseSelect* pSelect = select;
	if (pSelect == nullptr)
	{
		return nullptr;
	}
	pSelect->SetPos(pos);
	pSelect->SetType(OBJECT_TYPE_PAUSE_SELECT);
	pSelect->Init();
	return pSelect;
}