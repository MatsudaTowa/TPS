//=============================================
//
//�X���[�N�͈͏���[somoke_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_range.h"
#include "manager.h"

//���f���p�X
const char* CSmokeRange::MODEL_NAME = "data\\MODEL\\Container000.x";

//=============================================
//�R���X�g���N�^
//=============================================
CSmokeRange::CSmokeRange(int nPriority):CObjectX(nPriority)
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
}

//=============================================
//�`��
//=============================================
void CSmokeRange::Draw()
{
	CObjectX::Draw(D3DXCOLOR(1.0f,1.0f,1.0f,0.2f));
}

//=============================================
//����
//=============================================
CSmokeRange* CSmokeRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CSmokeRange* pSmokeRange = new CSmokeRange;

	if (pSmokeRange == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	//X�t�@�C���ǂݍ���
	pSmokeRange->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pSmokeRange->SetPos(pos);
	pSmokeRange->SetRot(rot);
	pSmokeRange->Init();

	return pSmokeRange;
}
