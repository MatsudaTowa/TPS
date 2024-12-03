//=============================================
//
//�X���[�N�͈͏���[somoke_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_range.h"
#include "manager.h"

//���f���p�X
const char* CSmokeRange::MODEL_NAME = "data\\MODEL\\colision.x";

//=============================================
//�R���X�g���N�^
//=============================================
CSmokeRange::CSmokeRange(int nPriority):CObjectX(nPriority), m_nLife(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSmokeRange::~CSmokeRange()
{
}

//=============================================
//������
//=============================================
HRESULT CSmokeRange::Init()
{
	CObjectX::Init();
	m_nLife = CSmoke::SMOKE_LIFE;
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSmokeRange::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSmokeRange::Update()
{
	CObjectX::Update();
	if (m_nLife > 0)
	{
		--m_nLife;
	}
	else
	{
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CSmokeRange::Draw()
{
#ifdef _DEBUG
	//CObjectX::Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

#endif // _DEBUG

}

//=============================================
//����
//=============================================
CSmokeRange* CSmokeRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CSmokeRange* pSmokeRange = new CSmokeRange;

	if (pSmokeRange == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	pSmokeRange->SetPos(pos);
	pSmokeRange->SetRot(rot);
	//X�t�@�C���ǂݍ���
	pSmokeRange->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);
	pSmokeRange->SetType(OBJECT_TYPE_SMOKE_RANGE);
	pSmokeRange->Init();

	return pSmokeRange;
}
