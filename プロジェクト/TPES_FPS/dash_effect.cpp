//=============================================
//
//�_�b�V�����ɃL�����N�^�[�̑O���ɏo���G�t�F�N�g[dash_effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "dash_effect.h"
#include "manager.h"

//x�t�@�C���̃t�@�C���p�X
const char* CDashEffect::MODEL_NAME = "data\\MODEL\\dash_effect.x";

//�X�P�[��
const D3DXVECTOR3 CDashEffect::SCALE = { 10.0f, 10.0f, 10.0f };

//�J���[
const D3DXCOLOR CDashEffect::COLOR = { 1.0f, 1.0f, 1.0f,0.35f };

//=============================================
//�R���X�g���N�^
//=============================================
CDashEffect::CDashEffect(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CDashEffect::~CDashEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CDashEffect::Init()
{
	//�`��ɕK�v�ȏ��ݒ�
	SetScale(SCALE);
	SetColor(COLOR);
	CObjectX::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CDashEffect::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CDashEffect::Update()
{
	CObjectX::Update();
}

//=============================================
//�`��
//=============================================
void CDashEffect::Draw()
{
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CDashEffect* CDashEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CDashEffect* pEffect = new CDashEffect;
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);

	pEffect->SetRot(rot);

	CModel* pModel = CManager::GetInstance()->GetModel();

	//X�t�@�C���ǂݍ���
	pEffect->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pEffect->SetType(OBJECT_TYPE_DUSH_EFFECT); //�^�C�v�ݒ�

	pEffect->Init();

	return pEffect;
}
