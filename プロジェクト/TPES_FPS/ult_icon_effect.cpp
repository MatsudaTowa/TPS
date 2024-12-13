//=============================================
//
//ult�����܂����Ƃ��ɃA�C�R������o���G�t�F�N�g[ult_icon_effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_icon_effect.h"
#include "manager.h"

const std::string CUltIconEffect::TEXTURE_NAME = "data\\TEXTURE\\ult_icon_effect_anim.png";

//=============================================
// �R���X�g���N�^
//=============================================
CUltIconEffect::CUltIconEffect(int nPriority):CObject2D_Anim(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
CUltIconEffect::~CUltIconEffect()
{
}

//=============================================
// ������
//=============================================
HRESULT CUltIconEffect::Init()
{
	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	//�e�N���X�̏�����
	CObject2D::Init();

	//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//�e�N�X�`���ړ��ʑ��
	SetTexMove(tex_move);

	//�e�N�X�`�����W�擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);

	//�A�j���[�V�����t���[�����
	SetAnimFrame(ANIMATION_FRAME);

	SetVtx(1.0f);

	//���_���W
	AnimationTex(tex_pos, tex_move);

	return S_OK;
}

//=============================================
// �I��
//=============================================
void CUltIconEffect::Uninit()
{
	CObject2D_Anim::Uninit();
}

//=============================================
// �X�V
//=============================================
void CUltIconEffect::Update()
{
	CObject2D_Anim::Update();

	//�e�N�X�`�����擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	//�A�j���[�V������̃e�N�X�`�����W�擾
	tex_pos = GetTexPos();
	//�A�j���[�V�������J��Ԃ�
	if (tex_pos.x >= 1.0f)
	{
		tex_pos.x = 0.0f;
	}
	SetTexPos(tex_pos);

	SetVtx(1.0f);

	//���_���W
	AnimationTex(tex_pos, tex_move);
}

//=============================================
// �`��
//=============================================
void CUltIconEffect::Draw()
{
	CObject2D_Anim::Draw();
}

//=============================================
// ����
//=============================================
CUltIconEffect* CUltIconEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CUltIconEffect* pIconEffect = new CUltIconEffect;

	//���g���Ȃ��Ȃ����̑O��return
	if(pIconEffect == nullptr) {return nullptr;}

	pIconEffect->SetPos(pos);
	pIconEffect->SetSize(size);
	pIconEffect->SetColor(col);

	pIconEffect->Init();

	return pIconEffect;
}
