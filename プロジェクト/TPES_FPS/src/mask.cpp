//=============================================
//
//�}�X�N����[mask.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mask.h"
#include "manager.h"

//=============================================
// �R���X�g���N�^
//=============================================
CMask::CMask(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CMask::~CMask()
{
}

//=============================================
// ������
//=============================================
HRESULT CMask::Init()
{
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,FLOAT_ZERO });

	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = COLOR_NONE;

	//�J���[����
	SetColor(col);

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void CMask::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void CMask::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// �`��
//=============================================
void CMask::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
CMask* CMask::Create(CMask* mask)
{
	CMask* pMask = mask;

	if (pMask == nullptr) { return nullptr; }

	pMask->Init();

	return pMask;
}
