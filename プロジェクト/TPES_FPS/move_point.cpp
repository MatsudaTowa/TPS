//=============================================
// 
//�G���p�j����ۂɌ������|�C���g[move_point.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "move_point.h"

//���Ԗڂ̒n�_��
int CMovePoint::m_NumPoint = 0;

const float CMovePoint::POINT_SIZE = 10.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CMovePoint::CMovePoint(int nPriority):CBillboard(nPriority)
{
	++m_NumPoint;
}

//=============================================
//�f�X�g���N�^
//=============================================
CMovePoint::~CMovePoint()
{
	--m_NumPoint;
}

//=============================================
//������
//=============================================
HRESULT CMovePoint::Init()
{
	SetSize(D3DXVECTOR3(POINT_SIZE,POINT_SIZE,0.0f));
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMovePoint::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMovePoint::Update()
{
	//�e�N���X�̍X�V����
	CObject3D::Update();
}

//=============================================
//�`��
//=============================================
void CMovePoint::Draw()
{
#ifdef _DEBUG
	CBillboard::Draw();
#endif // _DEBUG
}

//=============================================
//����
//=============================================
CMovePoint* CMovePoint::Create(D3DXVECTOR3 pos)
{
	CMovePoint* pMovePoint = new CMovePoint;
	if(pMovePoint == nullptr){ return nullptr; }

	//�ʒu�̐ݒ�
	pMovePoint->SetPos(pos);

	pMovePoint->Init();

	return pMovePoint;
}
