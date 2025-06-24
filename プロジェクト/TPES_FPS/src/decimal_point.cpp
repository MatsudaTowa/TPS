//=============================================
//
//�����_[decimal_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "decimal_point.h"

//=============================================
// �R���X�g���N�^
//=============================================
CDecimalPoint::CDecimalPoint(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CDecimalPoint::~CDecimalPoint()
{
}

//=============================================
// ������
//=============================================
HRESULT CDecimalPoint::Init()
{
	CObject2D::Init();
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CDecimalPoint::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CDecimalPoint::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// �`��
//=============================================
void CDecimalPoint::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CDecimalPoint* CDecimalPoint::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,D3DXCOLOR col)
{
	CDecimalPoint* point = new CDecimalPoint;

	if (point == nullptr) { return nullptr; }
	point->SetPos(pos);
	point->SetSize(size);
	point->SetColor(col);
	point->Init();
	return point;
}
