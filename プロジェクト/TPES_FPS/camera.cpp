//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"
#include "player.h"

//�ʏ�̈ړ����x
const float CCamera::DEFAULT_MOVE = 1.0f;

//�ʏ�̈ړ����x
const float CCamera::DAMPING_COEFFICIENT = 0.2f;

//�ʏ��Ԃ�Y�̋���
const float CCamera::DEFAULT_LENGTH_Y = 200.0f;

//�ʏ��Ԃ�Z�̋���
const float CCamera::DEFAULT_LENGTH_Z = 500.0f;

//�o�[�h�r���[����Y�̋���
const float CCamera::BIRDVIEW_LENGTH_Y = 300.0f;

//�T�C�h�r���[����X�̋���
const float CCamera::SIDEVIEW_LENGTH_X = 20.0f;

//�T�C�h�r���[����Y�̋���
const float CCamera::SIDEVIEW_LENGTH_Y = 50.0f;

//�T�C�h�r���[����Z�̋���
const float CCamera::SIDEVIEW_LENGTH_Z = 200.0f;

//�T�[�h�r���[���̕␳�l
const float CCamera::THIRDVIEW_CORRECT_X = 20.0f;
const float CCamera::THIRDVIEW_CORRECT_Y = 105.0f;
const float CCamera::THIRDVIEW_CORRECT_Z = 20.0f;

//�T�[�h�p�[�\���r���[����X�̍ő����
const float CCamera::MAX_TURN_X = 0.5f;
//�T�[�h�p�[�\���r���[����X�̍ŏ�����
const float CCamera::MIN_TURN_X = -0.15f;

//=============================================
//�R���X�g���N�^
//=============================================
CCamera::CCamera():

m_fAngle(0.0f),
m_fLength(0.0f),
m_moveR({0.0f,0.0f,0.0f}),
m_moveV({0.0f,0.0f,0.0f}),
m_mtxProjection(),
m_mtxView(),
m_pCameraState(),
m_posR({0.0f,0.0f,0.0f}),
m_posV({0.0f,0.0f,0.0f}),
m_rot({0.0f,0.0,0.0f}),
m_rotmove({0.0f,0.0f,0.0f}),
m_vecU({0.0f,0.0f,0.0f})
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CCamera::~CCamera()
{
}

//=============================================
//������
//=============================================
HRESULT CCamera::Init()
{
	if (m_pCameraState == nullptr)
	{
		m_pCameraState = new CThirdView;
	}
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -180.0f); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //������x�N�g��

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_�ړ���
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����_�ړ���

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�x
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //��]��

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CCamera::Uninit()
{
	if (m_pCameraState != nullptr)
	{
		delete m_pCameraState;
		m_pCameraState = nullptr;
	}
}

//=============================================
//�X�V
//=============================================
void CCamera::Update()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (m_pCameraState != nullptr)
	{
		m_pCameraState->ThirdView(this);
		m_pCameraState->FreeView(this);
		m_pCameraState->Ult(this);
	}

	//�}�E�X���擾
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();
	//���݂̃V�[�����擾 TODO:�V�[���Q�Ƃ����
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		m_rot.y += pMouse->GetMouseMove().x * 0.001f;
		m_rot.x += pMouse->GetMouseMove().y * 0.001f;
	}

	m_posV = m_posR + D3DXVECTOR3(-m_fLength * cosf(m_rot.x) * sinf(m_rot.y),
		m_fLength * sinf(m_rot.x),
		-m_fLength * cosf(m_rot.x) * cosf(m_rot.y));

	if (m_rot.x <= MIN_TURN_X)
	{
		m_rot.x = MIN_TURN_X;
	}
	if (m_rot.x >= MAX_TURN_X)
	{
		m_rot.x = MAX_TURN_X;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	m_posV += m_moveV;
	m_posR += m_moveR;

	//�ړ��ʂ��X�V(�����j
	m_moveV.x += (0.0f - m_moveV.x) * DAMPING_COEFFICIENT;
	m_moveV.y += (0.0f - m_moveV.y) * DAMPING_COEFFICIENT;
	m_moveV.z += (0.0f - m_moveV.z) * DAMPING_COEFFICIENT;

	m_moveR.x += (0.0f - m_moveR.x) * DAMPING_COEFFICIENT;
	m_moveR.y += (0.0f - m_moveR.y) * DAMPING_COEFFICIENT;
	m_moveR.z += (0.0f - m_moveR.z) * DAMPING_COEFFICIENT;

}

//=============================================
//�J�����ݒ�
//=============================================
void CCamera::SetCamera()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	posV.y += -15.0f;
	posR.y += -15.0f;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//======================================
//�J�������Z�b�g
//======================================
void CCamera::ResetCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 30.0f, -180.0f); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //������x�N�g��

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_�ړ���
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����_�ړ���

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�x
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //��]��

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);

}

//=============================================
//�J�����ړ���
//=============================================
void CCamera::InputMove()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_moveV.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_moveV.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_I) == true)
	{
		m_moveV.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_moveV.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
	}


	if (pKeyboard->GetPress(DIK_SPACE))
	{
		m_moveV.y += 1.0f;
		m_moveR.y += 1.0f;
	}

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		m_moveV.y -= 1.0f;
		m_moveR.y -= 1.0f;
	}
}

//=============================================
//�J�����̏�ԕύX
//=============================================
void CCamera::ChangeCameraState(CCameraState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pCameraState != nullptr)
	{
		delete m_pCameraState;
		m_pCameraState = state;
	}
}

//=============================================
//�J������]��
//=============================================
void CCamera::CameraTurn()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.02f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;

	}

	if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.02f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_rot.y -= 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_O) == true)
	{
		m_rot.y += 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}
}

//=============================================
//�T�[�h�p�[�\���r���[����
//=============================================
void CCamera::ThirdViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				m_posR.x = pPlayer->GetPos().x;
				m_posR.y = pPlayer->GetPos().y + THIRDVIEW_CORRECT_Y;
				m_posR.z = pPlayer->GetPos().z;

				////�J�������v���C���[�̉E�ɂ��鏈��:TODO
				//m_posR.x = pPlayer->GetPos().x + THIRDVIEW_CORRECT_X;
				//m_posR.y = pPlayer->GetPos().y + THIRDVIEW_CORRECT_Y;
				//m_posR.z = pPlayer->GetPos().z + THIRDVIEW_CORRECT_Z;

				m_posV = m_posR + D3DXVECTOR3(-m_fLength * cosf(m_rot.x) * sinf(m_rot.y),
					m_fLength * sinf(m_rot.x),
				-m_fLength * cosf(m_rot.x) * cosf(m_rot.y));

			}
		}
	}
}

//=============================================
//�J�����̕����擾
//=============================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//=============================================
//�J�����̎��_�擾
//=============================================
D3DXVECTOR3 CCamera::GetPosV()
{
	return m_posV;
}

//=============================================
//�J�����̒����_�擾
//=============================================
D3DXVECTOR3 CCamera::GetPosR()
{
	return m_posR;
}

//=============================================
//�����擾
//=============================================
float& CCamera::GetLength()
{
	return m_fLength;
}

//=============================================
//�J�����̃f�o�b�O�\��
//=============================================
void CCamera::DebugCameraDraw()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n\n\n[camera]\nposR:%.1f,%.1f,%.1f\nposV:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f"
		, m_posR.x, m_posR.y, m_posR.z, m_posV.x, m_posV.y, m_posV.z, m_rot.x, m_rot.y, m_rot.z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
