//=============================================
//
//3DTemplate[light.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CLight::CLight()
{
	//���C�g���̃N���A
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));
}

//=============================================
//�f�X�g���N�^
//=============================================
CLight::~CLight()
{
}

//=============================================
//������
//=============================================
HRESULT CLight::Init()
{
	//CRenderer* pRender = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; //�ݒ�����x�N�g��

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U���̐ݒ�
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCnt == 0)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 1)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, 0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.7f, -0.8f, -0.4f);
		}



		D3DXVec3Normalize(&vecDir, &vecDir); //���K��

		m_aLight[nCnt].Direction = vecDir;

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//���C�g��L����
		pDevice->LightEnable(nCnt, TRUE);
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CLight::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CLight::Update()
{
}
