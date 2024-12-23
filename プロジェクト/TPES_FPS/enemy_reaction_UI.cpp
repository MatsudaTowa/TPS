//=============================================
//
//�G�̃��A�N�V������UI[enemy_reaction_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_reaction_UI.h"
#include "enemy_confusion_UI.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy_Reaction_UI::CEnemy_Reaction_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy_Reaction_UI::~CEnemy_Reaction_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy_Reaction_UI::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy_Reaction_UI::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy_Reaction_UI::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//�`��
//=============================================
void CEnemy_Reaction_UI::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�e�N���X�̕`��
	CBillboard::Draw();
	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//����
//=============================================
CEnemy_Reaction_UI* CEnemy_Reaction_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, REACTION type)
{
	CEnemy_Reaction_UI* pReactionUI = nullptr;
	
	switch (type)
	{
	case CEnemy_Reaction_UI::REACTION_RELOAD:
		break;
	case CEnemy_Reaction_UI::REACTION_CONFUSION:
		pReactionUI = new CEnemy_Confusion_UI;
		break;
	case CEnemy_Reaction_UI::REACTION_STAN:
		break;
	default:
		assert(false);
		break;
	}
	if (pReactionUI == nullptr) { return nullptr; }

	pReactionUI->SetPos(pos);
	pReactionUI->SetSize(size);

	pReactionUI->Init();
	return pReactionUI;
}
