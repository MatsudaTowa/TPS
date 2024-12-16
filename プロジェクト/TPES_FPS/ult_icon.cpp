//=============================================
//
//�E���g�̃}�[�N�̕\�L[ult_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_icon.h"
#include "manager.h"

const D3DXCOLOR CUltIcon::START_COLOR = {0.2f,0.2f,0.2f,1.0f};

//=============================================
//�R���X�g���N�^
//=============================================
CUltIcon::CUltIcon(int nPriority):CObject2D(nPriority),
m_isAddColor(true),	//���Z��Ԃ�
m_AddColor(0.0f),	//�F�̉��Z�l������
m_pIconEffect()		//�A�C�R���̃G�t�F�N�g�|�C���^�[������
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CUltIcon::~CUltIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CUltIcon::Init()
{
	CObject2D::Init();

	//���_����
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CUltIcon::Uninit()
{
	if (m_pIconEffect != nullptr)
	{
		m_pIconEffect->Uninit();
		m_pIconEffect = nullptr;
	}
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CUltIcon::Update()
{
	CObject2D::Update();

	D3DXCOLOR col = GetColor();

	if (m_isAddColor)
	{
		col.r += m_AddColor;
		col.g += m_AddColor;
		col.b += m_AddColor;

		if (col.r >= 1.0f
			&& col.g >= 1.0f
			&& col.b >= 1.0f)
		{
			col = { 1.0f,1.0f,1.0f,1.0f };
			m_isAddColor = false; //���Z�I��

			if (m_pIconEffect == nullptr)
			{
				m_pIconEffect = CUltIconEffect::Create(GetPos(), { 75.0f,75.0f }, { 1.0f,0.8f,0.0f,0.75f });
			}
		}
	}

	SetColor(col);

	//���_����
	SetVtx(1.0f);
}

//=============================================
//�`��
//=============================================
void CUltIcon::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CUltIcon* CUltIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type)
{
	CUltIcon* pUltIcon = nullptr;

	switch (type)
	{
	case CUltIcon::ULT_TYPE_MEDIUM:
		pUltIcon = new CMediumIcon;
		break;
	default:
		assert(false);
		break;
	}

	//����̑O��return
	if(pUltIcon == nullptr) {return nullptr;}

	pUltIcon->SetPos(pos);

	pUltIcon->SetSize(size);

	pUltIcon->m_AddColor = add_col;

	pUltIcon->SetType(OBJECT_TYPE_ULT_ICON);

	pUltIcon->Init();

	return pUltIcon;
}

//=============================================
//�E���g���g�����ۂɌĂ΂��
//=============================================
void CUltIcon::Reset()
{
	SetColor(START_COLOR); //�F�������̐F��
	m_isAddColor = true; //���Z��Ԃ�

	if (m_pIconEffect != nullptr)
	{
		m_pIconEffect->Uninit();
		m_pIconEffect = nullptr;
	}
}

//�e�N�X�`��������
const std::string CMediumIcon::TEXTURE_NAME = "data\\TEXTURE\\ult_icon_000.png";
//=============================================
//�R���X�g���N�^
//=============================================
CMediumIcon::CMediumIcon(int nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMediumIcon::~CMediumIcon()
{
}

//=============================================
//������
//=============================================
HRESULT CMediumIcon::Init()
{
	SetColor(START_COLOR);
	//�e�N�X�`���ݒ�
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CUltIcon::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMediumIcon::Uninit()
{
	CUltIcon::Uninit();

}

//=============================================
//�X�V
//=============================================
void CMediumIcon::Update()
{
	CUltIcon::Update();
}

//=============================================
//�`��
//=============================================
void CMediumIcon::Draw()
{
	CUltIcon::Draw();
}
