//=============================================
//
//�t�F�[�h����[fade.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "fade.h"
#include"manager.h"

//�A���t�@�l������
const float CFade::FADE_VALUE = 0.05f;

//=============================================
//�R���X�g���N�^
//=============================================
CFade::CFade(int nPriority):CObject2D(nPriority),m_fademode()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFade::~CFade()
{
}

//=============================================
//������
//=============================================
HRESULT CFade::Init()
{
	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�T�C�Y����
	SetSize(size);

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade);

	//�J���[����
	SetColor(col);

	//���_�ݒ�
	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFade::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFade::Update()
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_colorFade -= FADE_VALUE;
			if (m_colorFade <= 0.0f)
			{
				m_colorFade = 0.0f;
				m_fade = FADE_NONE; //�������ĂȂ���Ԃ�
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_colorFade += FADE_VALUE;
			if (m_colorFade >= 1.0f)
			{
				m_colorFade = 1.0f;
				m_fade = FADE_IN; //�t�F�[�h�C����Ԃ�
				CManager::GetInstance()->SetMode(m_fademode);
			}
		}

		//�J���[�擾
		D3DXCOLOR col = GetColor();

		col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade);

		//�J���[����
		SetColor(col);

		//���_�J���[�̐ݒ�
		SetVtx(1.0f);
	}

}

//=============================================
//�`��
//=============================================
void CFade::Draw()
{
	CObject2D::Draw();
}

//=============================================
//�t�F�[�h�̐ݒ�
//=============================================
void CFade::SetFade(CScene::MODE modeNext)
{
    m_fademode = modeNext;
    m_fade = FADE_OUT;
}

////=============================================
////�t�F�[�h�̏��擾
////=============================================
////CFade::FADE CFade::GetFade(void)
////{
////    return m_fade;
////}

//=============================================
//�t�F�[�h�̐F�擾(��ɃA���t�@�l)
//=============================================
float CFade::FadeColor(void)
{
    return m_colorFade;
}

//=============================================
//����
//=============================================
CFade* CFade::Create(D3DXVECTOR3 pos)
{
	CFade* pFade = new CFade;
	//CObject *pObject = Getobject();
	if (pFade != nullptr)
	{
		pFade->SetPos(pos); //pos�ݒ�

		pFade->m_colorFade = 0.0f;

		pFade->SetType(OBJECT_TYPE_FADE); //�^�C�v�ݒ�

		//pResult_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pFade->Init();
	}
	return pFade;
}
